/***************************************
 * THIS PROGRAM GENERATES DOCUMENTARY
 * BY ANALIZING AND REWRITING COMMENTS FROM
 * YOUR FILE TO NEW .html file
 * PROGRAM DEVELOPED BY
 * @MOSKALT AND @MOROZOV312
 * 2020
 * THE PROGRAMM IS OPENSOURCE PROJECT
 * PROJECT SOURCE CODE
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
/*  removes multi-line comment characters
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
/* creates a unique file name which takes
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
    char* temp_filename = filename_without_extension(path); // need free
    char* generated_filename_temp = strcat(temp_filename, "__");
    char* generated_filename = (char*)calloc(550, sizeof(char)); // need free;
    strcpy(generated_filename, generated_filename_temp);
    free(temp_filename);
    generated_filename = strcat(generated_filename, str_time);
    char* folder_name = (char*)calloc(550, sizeof(char)); // need free
    char docs_path[] = "./docs/";
    for (int i = 0; docs_path[i] != '\0'; i++) {
        folder_name[i] = docs_path[i];
    }
    char* folder = strcat(folder_name, generated_filename);
    char* filename_html = strcat(folder, ".html");
    return filename_html;
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
    }
    if (!strcmp(extension, "c")) {
        return "<i>Program code in language C</i></br></br>";
    }
    if (!strcmp(extension, "cpp")) {
        return "<i>Program code in language C++</i></br></br>";
    }
    return "";
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

int html_generator(struct comment* list, char* path, int quan_structs)
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
    for (int i = 0; i < quan_structs; i++) {
        if (strlen(list[i].comment_data)) {
            fputs("<p class=\"comment\">", documentary);
            fputs(list[i].comment_data, documentary);
            fputs("</br></p>", documentary);
        }
        if (strlen(list[i].code_string)) {
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
