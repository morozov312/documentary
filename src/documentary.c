#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max_len_inp_str 500
#define max_quan_str 50 * 1000
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
    char* temp_filename
            = (char*)calloc((filename_estimate_lenght + 20), sizeof(char));
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
    char* folder_name = (char*)calloc(550, sizeof(char));
    folder_name[0] = '.';
    folder_name[1] = '/';
    folder_name[2] = 'd';
    folder_name[3] = 'o';
    folder_name[4] = 'c';
    folder_name[5] = 's';
    folder_name[6] = '/';
    char* folder = strcat(folder_name, generated_filename);
    char* filename_html = strcat(folder, ".html");
    return filename_html;
}
int html_generator(struct comment* list, char* path, int quan_structs)
{
    FILE* documentary;
    char* name = file_name_generator(path);
    documentary = fopen(name, "w");
    if (documentary == NULL) {
        printf("%s\n", "Error create html page!");
        return 0;
    }
    // ======================= Header ===========================
    fputs("<!DOCTYPE html><html><head><meta charset=\" UTF - 8\" >",
          documentary);
    fputs("<link rel=\"stylesheet\" type=\"text/css\" "
          "href=\"./styles/styles.css\">",
          documentary);
    fputs("</head><body><div id=\"wrapper\">", documentary);
    fputs("<h2>This documentation is based on a file -", documentary);
    // char* filename = filename_handle();
    // fputs(filename, documentary);
    fputs("</h2>", documentary);
    int flag = 0;
    for (int i = 0; i < quan_structs; i++) {
        if (list[i].type) { // check presence of multiline comment indocument
            flag++;
        }
    }
    char* expantion = expansion_handle(path);
    if (!strcmp(expantion, "h")) {
        fputs("<i>Header file to program code on C/C++</i></br></br>",
              documentary);
    }
    if (!strcmp(expantion, "c")) {
        fputs("<i>Program code in language C</i></br></br>", documentary);
    }
    if (!strcmp(expantion, "cpp")) {
        fputs("<i>Program code in language C++</i></br></br>", documentary);
    }
    fputs("<b>Warning</b></br></br><i>This documentation is based on the "
          "program code containing </br> ",
          documentary);
    if (flag) {
        fputs("documentary comments and is <u>officially</u> confirmed by",
              documentary);
    } else {
        fputs("only one-line comments and <u>may not be officially</u> "
              "confirmed by ",
              documentary);
    }
    fputs("the developer this program.</i></br></br>", documentary);
    // ====================== main content =====================
    for (int i = 0; i < quan_structs; i++) {
        int j = 0;
        while (j < max_quan_str) {
            int len = strlen(list[i].comment_data[j]);
            if (len == 0) {
                break;
            }
            fputs("<p class=\"comment\">", documentary);
            fputs(list[i].comment_data[j], documentary);
            fputs("</br>", documentary);
            j++;
        }
        fputs("</p>", documentary);
        fputs("<code>", documentary);
        fputs(list[i].code_temp_string, documentary);
        fputs("</code></br></br>", documentary);
    }
    // =======================   footer =========================
    fputs("</div></body></html>", documentary);
    fclose(documentary);
    return 0;
}
int docs_gen(char** document_data, char* path)
{
    int count_of_lines = 0;
    for (int i = 0; i < max_quan_str; i++) {
        if (strlen(document_data[i]) != 0) {
            count_of_lines++;
        }
    }
    int quan_struct = 0;
    struct comment* comments_array
            = (struct comment*)calloc(count_of_lines, sizeof(struct comment));
    for (int i = 0; i < count_of_lines - 2; i++) {
        if (single_comment_check(document_data[i])) {
            if (!muitiline_comment_begin_check(document_data[i + 1])
                && !muitiline_comment_end_check(document_data[i + 1])) {
                comments_array[quan_struct].code_temp_string
                        = document_data[i + 1];
                char** comment_text
                        = (char**)calloc(max_quan_str, sizeof(char*));
                for (int j = 0; j < max_quan_str; j++) {
                    comment_text[j]
                            = (char*)calloc(max_len_inp_str, sizeof(char));
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
    return 0;
}