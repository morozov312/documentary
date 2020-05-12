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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len_inp_str 500
#define max_quan_str 50000
#define qty_of_extentions 3
// This function handles expansion from path
char* get_file_extension(const char* file_path)
{
    char* dot_ptr = strrchr(file_path, '.');
    return dot_ptr == NULL ? "" : dot_ptr + 1;
}
// This function handles filename deleting expansion
const char* filename_without_extension(char* path)
{
    char* temp_path = (char*)calloc(strlen(path), sizeof(char*));
    strcpy(temp_path, path);
    char* p_last_dot = strrchr(path, '.');
    int last_dot_index = p_last_dot - path;
    temp_path[last_dot_index] = '\0';
    char* p_last_slash = strrchr(temp_path, '/');
    free(temp_path);
    return p_last_slash == NULL ? "" : p_last_slash + 1;
}
// This function checks file's expansion
char* exclude_html(char* str) // need memory clear
{
    int len = (int)strlen(str);
    /* in the worst case, the string is increased 3 times + end of line
     * character*/
    str = (char*)realloc(str, (len * 3) + 1);
    int j = 0;
    for (int i = 0; i < len; i++, j++) {
        if (str[i] == '<') {
            str[j] = '&';
            str[j + 1] = 'l';
            str[j + 2] = 't';
            j += 2;
        } else if (str[i] == '>') {
            str[j] = '&';
            str[j + 1] = 'g';
            str[j + 2] = 't';
            j += 2;
        } else {
            str[j] = str[i];
        }
    }
    str[j] = '\0';
    return str;
}
int extension_check(char* filepath)
{
    char* valid_extentions[qty_of_extentions] = {"cpp", "h", "c"};
    int flag = 0;
    char* temp = get_file_extension(filepath);
    for (int i = 0; i < qty_of_extentions; i++) {
        flag = strcmp(temp, valid_extentions[i]);
        if (flag == 0) {
            return 1;
        }
    }
    return 0;
}
// This function checks single comments
int single_comment_check(char* str)
{
    unsigned int len = strlen(str);
    int flag = 0;
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '/' && str[i + 1] == '/') {
            flag++;
            i++;
        }
    }
    return flag > 0 ? 1 : 0;
}

int check_single_documentary_comment(char* string)
{
    char* ptr_slash = strchr(string, '/');
    if (single_comment_check(string) == 1) {
        if (ptr_slash[2] == '/' || ptr_slash[2] == '!')
            return 1;
        else
            return 0;
    }
    return 0;
}
// This function checks multiline comment's begin
int multiline_comment_begin_check(char* str)
{
    unsigned int len = strlen(str);
    int flag = 0; // can be rewritten
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '/' && str[i + 1] == '*') {
            flag++;
        }
    }
    return flag > 0 ? 1 : 0;
}
// This function checks multiline comment's end
int multiline_comment_end_check(char* str)
{
    unsigned int len = strlen(str);
    int flag = 0;
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '*' && str[i + 1] == '/') {
            flag++;
        }
    }
    return flag > 0 ? 1 : 0;
}

int check_document_multiline_commentary(char* string)
{
    char* ptr_first_star = strchr(string, '*');
    if (multiline_comment_begin_check(string) == 1) {
        if ((ptr_first_star)[1] == '*' || (ptr_first_star)[1] == '!') {
            return 1; // valid comment
        } else {
            return 0; // invalid comment
        }
    } else
        return 0;
}
// This function return array of data from file
char** get_data_from_document(char* paths) // need memory clear
{
    FILE* myfile;
    myfile = fopen(paths, "r");
    if (myfile == NULL) {
        printf("%s%s%s\n", "On path ", paths, " file not found!");
        return 0;
    }
    char* ptrFile;
    int quan_str = 0;
    char** data = (char**)calloc(max_quan_str, sizeof(char*));
    for (int i = 0; i < max_quan_str; i++) {
        data[i] = (char*)calloc(max_len_inp_str, sizeof(char));
    }
    while (quan_str < max_quan_str) {
        char* temp = (char*)calloc(max_len_inp_str, sizeof(char));
        ptrFile = fgets(temp, max_len_inp_str, myfile);
        if (ptrFile == NULL) {
            if (feof(myfile) != 0) {
                break;
            } else {
                continue;
            }
        }
        strcpy(data[quan_str], temp);
        quan_str++;
        free(temp);
    }
    fclose(myfile);
    return data;
}
char* get_inpdir(int qty, char* array_argv[])
{
    const char input_directory[] = "-inpdir";
    const char output_directory[] = "-outdir";
    for (int i = 1; i < qty; i++) {
        if (strcmp(array_argv[i], input_directory) != 0
            && strcmp(array_argv[i], output_directory) != 0) {
            printf("%s%s\n", "Unknown option: ", array_argv[i]);
            continue;
        }
        if (strcmp(array_argv[i], output_directory) == 0) {
            i++;
            continue;
        }
        if (strcmp(array_argv[i], input_directory) == 0) {
            return array_argv[i + 1];
        }
    }
    return "";
}
char* get_outdir(int qty, char* array_argv[])
{
    const char input_directory[] = "-inpdir";
    const char output_directory[] = "-outdir";
    for (int i = 1; i < qty; i++) {
        if (strcmp(array_argv[i], input_directory) != 0
            && strcmp(array_argv[i], output_directory) != 0) {
            printf("%s%s\n", "Unknown option: ", array_argv[i]);
            continue;
        }
        if (strcmp(array_argv[i], input_directory) == 0) {
            i++;
            continue;
        }
        if (strcmp(array_argv[i], output_directory) == 0) {
            return array_argv[i + 1];
        }
    }
    return "";
}