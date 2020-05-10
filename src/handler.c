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
// This function handles expansion from path
char* expansion_handle(char* str)
{
    int max_len_expan = 4;
    char* expansion = (char*)calloc(max_len_expan, sizeof(char));
    int len_path = (int)strlen(str);
    int j = 0;
    for (int i = len_path - 1; i != 0; i--) {
        expansion[j] = str[i];
        j++;
        if (str[i - 1] == '.' || j == 3) {
            break;
        }
    }
    int exp_temp_len = (int)strlen(expansion);
    char* reversed_str = (char*)calloc(exp_temp_len, sizeof(char));
    char buff = 0;
    int k = 0;
    for (int i = exp_temp_len - 1; i >= 0; i--) {
        buff = expansion[i];
        reversed_str[k] = buff;
        k++;
    }
    // returns file extension for next checks
    return reversed_str;
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
int expan_check(char* filepath)
{
    const int quan_of_expan = 3;
    const char exps[3][4] = {"cpp", "c", "h"};
    int flag = 0;
    char* temp = expansion_handle(filepath);
    for (int i = 0; i < quan_of_expan; i++) {
        flag = strcmp(temp, exps[i]);
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
        }
    }
    if (flag == 1) {
        return 1;
    }
    if (flag > 1) {
        printf("%s", "Error,don't use nested comments");
        return -1;
    }
    return 0;
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
    if (flag == 1) {
        return 1;
    }
    if (flag > 1) {
        printf("%s", "Error,don't use nested comments");
        return -1;
    }
    return 0;
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
    if (flag == 1) {
        return 1;
    }
    if (flag > 1) {
        printf("%s", "Error,don't use nested comments");
        return -1;
    }
    return 0;
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
