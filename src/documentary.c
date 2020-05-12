/***************************************
 * THIS PROGRAM GENERATES DOCUMENTARY
 * BY ANALIZING AND REWRITING COMMENTS FROM
 * YOUR FILE TO NEW .html file
 * PROGRAM DEVELOPED BY
 * @MOSKALT AND @MOROZOV312
 * 2020
 * THE PROGRAMM IS OPENSOURCE PROJECT
 * PROJECT'S SOURCE CODE
 * https://github.com/morozov312/documentary
 ****************************************/

#include "handler.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max_len_inp_str 500
#define max_quan_str 50 * 1000
struct comment {
    char* comment_data;
    char* code_string;
};
/*!  removes multi-line comment characters
 * for a more understandable entry in html page */

int counter = 0;

char* del_documentary_comment_symbols(char* string)
{
    char* ptr_slash = strchr(string, '/');
    return ptr_slash == NULL ? "" : ptr_slash + 3;
}
char* del_multiline_comment_begin(char* str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/' && str[i + 1] == '*') {
            str[i] = ' ';
            str[i + 1] = ' ';
        }
    }
    return str;
}
char* del_multiline_comment_end(char* str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*' && str[i + 1] == '/') {
            str[i] = ' ';
            str[i + 1] = ' ';
        }
    }
    return str;
}
char* del_multiline_comment_stars(char* str)
{
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] != ' ' && str[i] != '*') {
            break;
        } else if (str[i] != ' ' && str[i] == '*') {
            str[i] = ' ';
            break;
        }
    }
    return str;
}
/*! creates a unique file name which takes
 * the name, day, number and time of creation of the documentation */
char* file_name_generator(char* path)
{
    long int s_time = 0;
    struct tm* m_time;
    s_time = time(NULL);
    m_time = localtime(&s_time);
    char* str_time = asctime(m_time);
    for (int i = 0; str_time[i] != '\0'; i++) {
        if (str_time[i] == ' ') {
            str_time[i] = '_';
        }
    }
    unsigned int len = strlen(str_time) - 1;
    if (str_time[len] == '\n') {
        str_time[len] = '\0';
    }
    char filename[1000];
    sprintf(filename,
            "%s%s%s%s%s",
            "./docs/",
            str_time,
            "_",
            filename_without_extension(path),
            ".html");
    return filename;
}
/**********************************************************
 * this function creates an HTML page from the documentation
 * in the directory - documentary/docs/
 **********************************************************/
char* get_document_type(char* path)
{
    char* extension = get_file_extension(path);
    if (!strcmp(extension, "h")) {
        return "<i>Header file to program code on C/C++</i></br></br>";
    } else if (!strcmp(extension, "c")) {
        return "<i>Program code in language C</i></br></br>";
    } else if (!strcmp(extension, "cpp")) {
        return "<i>Program code in language C++</i></br></br>";
    } else {
        return "";
    }
}
void recursive_files_search(char* path, char** paths)
{
    DIR* d = opendir(path);
    if (d == NULL)
        return;
    struct dirent* dir;
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_type != DT_DIR) {
            char* f_path = (char*)calloc(100, sizeof(char));
            sprintf(f_path, "%s/%s", path, dir->d_name);
            strcpy(paths[counter], f_path);
            free(f_path);
            counter++;

        } else if (
                dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0
                && strcmp(dir->d_name, "..") != 0) {
            char d_path[255];
            sprintf(d_path, "%s/%s", path, dir->d_name);
            recursive_files_search(d_path, paths);
        }
    }
    closedir(d);
}

int html_generator(struct comment* list, char* path, int qty_structs)
{
    FILE *documentary, *styles;
    char* ptrFile;
    char* name = file_name_generator(path);
    documentary = fopen(name, "w");
    if (documentary == NULL) {
        printf("%s\n", "Error create html page!");
        return 0;
    }
    // Header
    styles = fopen("./styles/styles.html", "r");
    if (styles == NULL) {
        printf("%s\n", "Stylesheet not found!");
        return 0;
    }
    while (1) {
        char* temp = (char*)calloc(max_len_inp_str, sizeof(char));
        ptrFile = fgets(temp, max_len_inp_str, styles);
        if (ptrFile == NULL) {
            if (feof(styles) != 0) {
                break;
            } else {
                continue;
            }
        }
        fputs(temp, documentary);
        free(temp);
    }
    fclose(styles);
    char* filename = filename_without_extension(path);
    fputs(filename, documentary);
    fputs("</h2>", documentary);
    // document programming language definition
    fputs(get_document_type(path), documentary);
    // main content
    for (int i = 0; i < qty_structs; i++) {
        if (list[i].comment_data) {
            fputs("<p class=\"comment\">", documentary);
            fputs(list[i].comment_data, documentary);
            fputs("</br></p>", documentary);
        }
        if (list[i].code_string) {
            fputs("<code>", documentary);
            fputs(list[i].code_string, documentary);
            fputs("</code></br></br>", documentary);
        }
    }
    // Footer
    fputs("</div></body></html>", documentary);
    fclose(documentary);
    return 1;
}
int code_check(char* str)
{
    int single = single_comment_check(str);
    int m_b = multiline_comment_begin_check(str);
    int m_e = multiline_comment_end_check(str);
    if (!single && !m_b && !m_e) {
        return 1;
    }
    return 0;
}
struct comment* create(int count, char** doc)
{
    struct comment* comments_array
            = (struct comment*)calloc(count, sizeof(struct comment));
    int qty = 0;
    for (int i = 0; i < count; i++) {
        char* current_str = doc[i];
        char* next_str = doc[i];
        if (check_single_documentary_comment(current_str)) {
            comments_array[qty].comment_data
                    = del_documentary_comment_symbols(current_str);
            if (code_check(next_str)) {
                comments_array[qty].code_string = doc[i + 1];
            } else {
                comments_array[qty].code_string = "";
            }
            qty++;
        }
    }
    return comments_array;
};
int document_creation(char* path)
{
    char** document_data = get_data_from_document(path);
    int count_of_lines = 0, qty_structs = 0;
    for (int i = 0; i < max_quan_str; i++) {
        if (strlen(document_data[i]) != 0) {
            document_data[i] = exclude_html(document_data[i]);
            // printf("%s\n", document_data[i]);
            count_of_lines++;
        }
    }
    /// this error appears if the document empty ot has 1 line
    if (count_of_lines <= 1) {
        printf("%s%s", "Error,file on path ", path);
        printf("%s\n", " too small for documentation");
        return 0;
    }
    struct comment* comments_array = create(count_of_lines, document_data);
    for (int i = 0; i < count_of_lines; i++) {
        if (comments_array[i].comment_data != NULL) {
            qty_structs++;
        }
    }
    if (qty_structs == 0) {
        printf("%s\n", "error 1111");
        return 0;
    }
    int res = html_generator(comments_array, path, qty_structs);
    if (res) {
        printf("%s\n", "success");
    }
    for (int i = 0; i < max_quan_str; i++) {
        free(document_data[i]);
    }
    free(document_data);
    free(comments_array);
    return 0;
}