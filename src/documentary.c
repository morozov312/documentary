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
char* file_name_generator(char* path)
{
    int last_index;
    int temp = 0;
    int filename_estimate_lengh = strlen(path);
    long int s_time;
    struct tm* m_time;
    int last_index_dot = 0;
    s_time = time(NULL);
    m_time = localtime(&s_time);
    char* str_time = asctime(m_time);
    for (int i = 0; i < strlen(str_time); i++) {
        if (str_time[i] == ' ') {
            str_time[i] = '_';
        }
    }
    char* temp_filename = (char*)malloc(
            (filename_estimate_lengh + 5)
            * sizeof(char)); // 12 is estimated count of chars for time
    for (int i = 0; i < filename_estimate_lengh; i++) {
        if (path[i] == '/') {
            last_index = i;
        } else if (path[i] == '.') {
            last_index_dot = i;
        }
    }
    for (int i = last_index + 1; i < last_index_dot; i++) {
        temp_filename[temp] = path[i];
        temp++;
    }
    for (int i = (last_index_dot - last_index); i < strlen(temp_filename);
         i++) {
        temp_filename[i] = '_';
    }
    char* generated_filename = strcat(temp_filename, str_time);
    return generated_filename;
}

int docs_gen(char** array, char* path) // not finished
{
    int count_of_lines;
    int index_of_end;
    int j, k;
    const int MAX_STR_LEN = 1000;
    count_of_lines = sizeof(array) / sizeof(array[0]);
    struct comment* comments_array
            = (struct comment*)malloc(count_of_lines * sizeof(struct comment));
    char** temp_array = (char**)malloc(count_of_lines * sizeof(char*));
    for (int i = 0; i < count_of_lines; i++) {
        temp_array[i] = (char*)malloc(MAX_STR_LEN * sizeof(char));
    }
    int struct_line_number = 0;
    for (int i = 0; i < count_of_lines - 1; i++) {
        if (single_comment_check(array[i]) == -1) { // switch for more cases
            return 1;                               // exit after nested comment
        } else if (single_comment_check(array[i]) == 1) {
            temp_array[struct_line_number] = del_single_comment(array[i]);
            comments_array[struct_line_number].type = 0;
            comments_array[struct_line_number].comment_data[0]
                    = temp_array[struct_line_number];
            if (single_comment_check(array[i + 1]) == 0
                && muitiline_comment_begin_check(array[i + 1]) == 0) {
                temp_array[struct_line_number] = array[i + 1];
                comments_array[struct_line_number].code_temp_string
                        = temp_array[struct_line_number];
            }
            struct_line_number++;
            continue;
        } else if (muitiline_comment_begin_check(array[i]) == 1) {
            j = i;
            while (muitiline_comment_end_check(array[j + 1]) != 1) {
                if (single_comment_check(array[j + 1]) == 1) {
                    return 2; // single comment in multiline comment
                } else if (muitiline_comment_begin_check(array[j + 1]) == 1) {
                    return 3; // nested comment
                }
                j++;
            }
            for (k = i; i < j + 1; k++) {
                if (muitiline_comment_begin_check(array[k] == 1)) {
                    temp_array[struct_line_number]
                            = del_multiline_comment_begin(array[k]);
                    comments_array[struct_line_number].type = 1;
                    comments_array[struct_line_number].comment_data
                            = temp_array[struct_line_number];
                    struct_line_number++;
                } else if (muitiline_comment_end_check(array[k] == 1)) {
                    temp_array[struct_line_number]
                            = del_multiline_comment_end(array[k]);
                    comments_array[struct_line_number].type = 1;
                    comments_array[struct_line_number].comment_data
                            = temp_array[struct_line_number];
                    temp_array[struct_line_number] = array[k + 1];
                    comments_array[struct_line_number].code_temp_string
                            = temp_array[struct_line_number];
                    struct_line_number++;

                } else {
                    temp_array[struct_line_number] = array[k];
                    comments_array[struct_line_number].type = 1;
                    comments_array[struct_line_number].comment_data
                            = temp_array[struct_line_number];
                    struct_line_number++;
                }
            }
        }
    }
}