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
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/' && str[i + 1] == '/') {
            str[i] = ' ';
            str[i + 1] = ' ';
            break;
        }
    }
    return str;
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
    int last_index = 0;
    int temp = 0;
    int filename_estimate_lenght = strlen(path);
    long int s_time = 0;
    struct tm* m_time;
    int last_index_dot = 0;
    s_time = time(NULL);
    m_time = localtime(&s_time);
    char* str_time = asctime(m_time);
    for (int i = 0; str_time[i] != '\0'; i++) {
        if (str_time[i] == ' ') {
            str_time[i] = '_';
        }
    }
    int len = strlen(str_time) - 1;
    if (str_time[len] == '\n') {
        str_time[len] = '\0';
    }
    char* temp_filename = (char*)malloc(
            (filename_estimate_lenght + 5)
            * sizeof(char)); // 12 is estimated count of chars for time
    for (int i = 0; i < filename_estimate_lenght + 5; i++) {
        temp_filename[i] = 0;
    }

    for (int i = 0; i < filename_estimate_lenght; i++) {
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
    for (int i = (last_index_dot - last_index); temp_filename[i] != '\0'; i++) {
        temp_filename[i] = '_';
    }
    char* generated_filename = strcat(temp_filename, str_time);
    char* filename_html = strcat(generated_filename, ".html");
    free(temp_filename);
    return filename_html;
}
int html_generator(struct comment* list, char* path, int quan_structs)
{
    FILE* documentary;
    char* name = file_name_generator(path);
    documentary = fopen(name, "w");
    if (documentary == NULL) {
        printf("%s\n", "Error! Not enough free memory to create html page!");
        return 0;
    }
    int flag = 0;
    int max_quan_str = 50 * 1000;
    for (int i = 0; i < quan_structs; i++) {
        if (list[i].type) { // check presence of multiline comment in document
            flag++;
        }
    }
    fputs("<h2><b>HOME</b><h2></br>", documentary);
    if (flag) {
        fputs("Oficial</br>", documentary);
    } else {
        fputs("Not</br>", documentary);
    }
    for (int i = 0; i < quan_structs; i++) {
        int j = 0;
        char** text_comment = list[i].comment_data;
        while (j < max_quan_str) {
            int len = strlen(text_comment[j]);
            if (len == 0) {
                break;
            }
            fputs(list[i].comment_data[j], documentary);
            fputs("</br>", documentary);
            j++;
        }
        fputs("</br>", documentary);
        fputs(list[i].code_temp_string, documentary);
        fputs("</br>", documentary);
    }
    fclose(documentary);
    return 0;
}
int docs_gen(char** document_data, char* path)
{
    int count_of_lines = 0;
    int max_quan_str = 50 * 1000;
    for (int i = 0; i < max_quan_str; i++) {
        if (strlen(document_data[i]) != 0) {
            count_of_lines++;
        }
    }
    int quan_struct = 0;
    const int MAX_STR_LEN = 500;
    struct comment* comments_array
            = (struct comment*)malloc(count_of_lines * sizeof(struct comment));
    for (int i = 0; i < count_of_lines - 2; i++) {
        if (single_comment_check(document_data[i])) {
            if (!muitiline_comment_begin_check(document_data[i + 1])
                && !muitiline_comment_end_check(document_data[i + 1])) {
                comments_array[quan_struct].code_temp_string
                        = document_data[i + 1];
                char** comment_text
                        = (char**)malloc(max_quan_str * sizeof(char*));
                for (int j = 0; j < max_quan_str; j++) {
                    comment_text[j] = (char*)malloc(MAX_STR_LEN * sizeof(char));
                }
                for (int ii = 0; ii < max_quan_str; ii++) {
                    for (int j = 0; j < MAX_STR_LEN; j++) {
                        comment_text[ii][j] = 0;
                    }
                }
                int num_of_st_comment = 0;
                comment_text[num_of_st_comment] = document_data[i];
                comments_array[quan_struct].comment_data = comment_text;
                comments_array[quan_struct].type = 0;
                quan_struct++;
            }
        }
    }
    html_generator(comments_array, path, quan_struct);
    free(comments_array);
    return 0;
}