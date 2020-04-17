#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int del_multiline_comment_begin()
{
    // may be on '/*' symbols writing ' '
    return 0;
}
int del_multiline_comment_end()
{
    // may be on '*/' symbols writing ' '
    return 0;
}
int del_multiline_comment_stars()
{
    // may be on '*' symbols writing ' '
    // often in multiline comments strings begining with *
    // must be del only first star on string
    return 0;
}

int docs_gen(char** array)
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
            continue;
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