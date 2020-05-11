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
char* filename_without_expan(char* path)
{
    unsigned int last_slash_index = 0;
    unsigned int last_dot_index = 0;
    for (unsigned int i = 0; i < strlen(path); i++) {
        if (path[i] == '/') {
            last_slash_index = i;
        } else if (path[i] == '.') {
            last_dot_index = i;
        }
    }
    unsigned int len_of_filename = last_dot_index - last_slash_index;
    char* filename = (char*)calloc(len_of_filename, sizeof(char));
    int counter = 0;
    for (unsigned int i = last_slash_index + 1; i < last_dot_index; i++) {
        filename[counter] = path[i];
        counter++;
    }
    // returns file name without extension
    // if it is impossible returns 0
    if (strlen(filename) < 1) {
        return 0;
    } else {
        return filename;
    }
}
// This function checks file's expansion
char* no_html(char* str)
{
    int len = (int)strlen(str);
    /* in the worst case, the string is increased 3 times + end of line
     * character*/
    char* no_html_str = (char*)calloc((len * 3) + 1, sizeof(char));
    int j = 0;
    for (int i = 0; i < len; i++, j++) {
        if (str[i] == '<') {
            no_html_str[j] = '&';
            no_html_str[j + 1] = 'l';
            no_html_str[j + 2] = 't';
            j += 2;
        } else if (str[i] == '>') {
            no_html_str[j] = '&';
            no_html_str[j + 1] = 'g';
            no_html_str[j + 2] = 't';
            j += 2;
        } else {
            no_html_str[j] = str[i];
        }
    }
    no_html_str[j] = '\0';
    return no_html_str;
}
int extention_check(char* filepath)
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
// This function checks multiline comment's begin
int multiline_comment_begin_check(char* str)
{
    unsigned int len = strlen(str);
    int flag = 0;
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
// This function return array of data from file
char** document_handle(char* paths)
{
    FILE* myfile;
    myfile = fopen(paths, "r");
    if (myfile == NULL) {
        printf("%s%s%s\n", "On path ", paths, " file not found!");
        return 0;
    }
    char *temp, *ptrFile;
    int quan_str = 0;
    char** data = (char**)calloc(max_quan_str, sizeof(char*));
    for (int i = 0; i < max_quan_str; i++) {
        data[i] = (char*)calloc(max_len_inp_str, sizeof(char));
    }
    while (quan_str < max_quan_str) {
        temp = (char*)calloc(max_len_inp_str, sizeof(char));
        ptrFile = fgets(temp, max_len_inp_str, myfile);
        if (ptrFile == NULL) {
            if (feof(myfile) != 0) {
                break;
            } else {
                continue;
            }
        }
        data[quan_str] = temp;
        quan_str++;
    }
    fclose(myfile);
    return data;
}
