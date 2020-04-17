#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct comment {
    int type; // 0 - single comment , 1 - multiline comment
    char** comment_data;
    char* code_temp_string;
};
char* del_single_comment(char* str)
{
    // may be on '//' symbols writing ' '
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '/' && str[i + 1] == '/') {
            str[i] = ' ';
            str[i + 1] = ' ';
            break;
        }
    }
    return str;
}
char* del_multiline_comment_begin(char str[])
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/' && str[i + 1] == '*') {
            str[i] = ' ';
            str[i + 1] = ' ';
        }
    }
    return str;
}
char* del_multiline_comment_end(char str[])
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*' && str[i + 1] == '/') {
            str[i] = ' ';
            str[i + 1] = ' ';
        }
    }
    return str;
}
char* del_multiline_comment_stars(char str[])
{
    int flag = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '*') {
            flag++;
        }
        if (str[i] == '*' && !flag) {
            str[i] = ' ';
        }
    }
    return str;
}
char* file_name_generator(char* path) // not finished
{
    int last_index;
    int temp = 0;
    int filename_estimate_lengh = strlen(path);
    char* temp_filename = (char*)malloc(
            (filename_estimate_lengh + 12)
            * sizeof(char)); // 12 is estimated count of chars for time
    for (int i = 0; i < filename_estimate_lengh; i++) {
        if (path[i] == '/') {
            last_index = i;
        }
    }

    for (int i = last_index; i < filename_estimate_lengh; i++) {
        if (path[i] != '.') {
            temp_filename[temp] = path[i];
            temp++;
        }
    }
}
int docs_gen(char** array, char* path) // not finished
{
    int count_of_lines;
    const int MAX_STR_LEN = 1000;
    count_of_lines = sizeof(array) / sizeof(array[0]);
    struct comment* comments_array
            = (struct comment*)malloc(count_of_lines * sizeof(struct comment));
    char** temp_array = (char**)malloc(count_of_lines * sizeof(char*));
    for (int i = 0; i < count_of_lines; i++) {
        temp_array[i] = (char*)malloc(MAX_STR_LEN * sizeof(char));
    }
    int struct_line_number = 0;
    for (int i = 0; i < count_of_lines; i++) {
        if (single_comment_check(array[i]) == -1) { // switch for more cases
            break;
        } else if (single_comment_check(array[i]) == 1) {
            temp_array[struct_line_number] = del_single_comment(array[i]);
            comments_array[struct_line_number].type = 0;
            comments_array[struct_line_number].comment_data[0]
                    = temp_array[struct_line_number];
            if (single_comment_check(array[i + 1]) == 0) {
                temp_array[struct_line_number]
                        = del_single_comment(array[i + 1]);
                comments_array[struct_line_number].code_temp_string
                        = temp_array[struct_line_number];
            }
            struct_line_number++;
        }
    }
}