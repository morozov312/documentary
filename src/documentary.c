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
    char* code_string;
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
    char* generated_filename_temp = strcat(temp_filename, "__");
    char* generated_filename = strcat(generated_filename_temp, str_time);
    char* folder_name = (char*)calloc(550, sizeof(char));
    char docs_path[] = "./docs/";
    for (int i = 0; docs_path[i] != '\0'; i++) {
        folder_name[i] = docs_path[i];
    }
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
    fputs("<h2>This documentation is shaped on file - ", documentary);
    char* filename = filename_without_expan(path);
    fputs(filename, documentary);
    fputs("</h2>", documentary);
    int flag = 0;
    for (int i = 0; i < quan_structs; i++) {
        // check presence of multiline comment indocument
        if (list[i].type) {
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
        if (strlen(list[i].code_string)) {
            fputs("<code>", documentary);
            fputs(list[i].code_string, documentary);
            fputs("</code></br></br>", documentary);
        }
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
    // this error appears if the document empty ot has 1 line
    if (count_of_lines <= 1) {
        printf("%s%s", "Error,file on path ", path);
        printf("%s\n", " too small for documentation");
        return 0;
    }
    int quan_struct = 0;
    struct comment* comments_array
            = (struct comment*)calloc(count_of_lines, sizeof(struct comment));
    char** multiline_comment = (char**)malloc(max_quan_str * sizeof(char*));
    for (int j = 0; j < max_quan_str; j++) {
        multiline_comment[j] = (char*)malloc(max_len_inp_str * sizeof(char));
    }
    for (int j = 0; j < max_quan_str; j++) {
        multiline_comment[j] = "";
    }
    // index of position in multiline comment
    int index = 0;
    // chek of begining multiline comment
    int begin = 0;
    for (int i = 0; i < count_of_lines - 1; i++) {
        int b_check = muitiline_comment_begin_check(document_data[i]);
        int e_check = muitiline_comment_end_check(document_data[i]);
        // multiline comment check
        if (b_check == 1 && !begin) {
            // nested comment chek
            if (b_check == -1) {
                return 0;
            }
            for (int j = 0; j < max_quan_str; j++) {
                multiline_comment[j] = "";
            }
            multiline_comment[index] = document_data[i];
            index++;
            begin++;
            comments_array[quan_struct].type = 1;
        }
        if (b_check == 1 && begin > 1) {
            // error
            return 0;
        }
        if (e_check == 1 && !begin) {
            // error
            return 0;
        }
        if (e_check == 0 && begin && b_check == 0) {
            multiline_comment[index] = document_data[i];
            index++;
        }
        if (e_check == 1 && begin) {
            // nested comment chek
            if (e_check == (-1)) {
                return 0;
            }
            int mb_check = 0;
            mb_check = muitiline_comment_begin_check(document_data[i + 1]);
            int me_chek = muitiline_comment_end_check(document_data[i + 1]);
            int ns_check = single_comment_check(document_data[i + 1]);
            // if next string is code
            multiline_comment[index] = document_data[i];
            index++;
            if (mb_check == 0 && me_chek == 0 && ns_check == 0) {
                comments_array[quan_struct].code_string = document_data[i + 1];
            } else {
                comments_array[quan_struct].code_string = "";
            }
            comments_array[quan_struct].comment_data = multiline_comment;
            quan_struct++;
            i++;
            index = 0;
            begin = 0;
        }
        // single comment check
        int s_check = single_comment_check(document_data[i]);
        if (s_check == 1 && !begin) {
            int oneline_comment_check = 0;
            oneline_comment_check = single_comment_code_check(document_data[i]);
            /* fill type of comment and adding empty code string for the case
             * when there are some comments in a row */
            comments_array[quan_struct].type = 0;
            comments_array[quan_struct].code_string = "";
            // nested comment chek
            if (s_check == -1) {
                return 0;
            }
            char** comment_text = (char**)malloc(max_quan_str * sizeof(char*));
            for (int j = 0; j < max_quan_str; j++) {
                comment_text[j] = (char*)malloc(max_len_inp_str * sizeof(char));
            }
            for (int j = 0; j < max_quan_str; j++) {
                comment_text[j] = "";
            }
            if (!oneline_comment_check) {
                comment_text[0] = del_single_comment(document_data[i]);
                int mb_check = 0;
                mb_check = muitiline_comment_begin_check(document_data[i + 1]);
                int me_chek = muitiline_comment_end_check(document_data[i + 1]);
                int ns_check = single_comment_check(document_data[i + 1]);
                // if next string is code
                if (mb_check == 0 && me_chek == 0 && ns_check == 0) {
                    comments_array[quan_struct].code_string
                            = document_data[i + 1];
                    i++;
                }
                // if on one line code and comment
            } else {
                char* code = code_from_string_with_comment(document_data[i]);
                char* comment = comment_from_string_with_code(document_data[i]);
                comments_array[quan_struct].code_string = code;
                comment_text[0] = del_single_comment(comment);
            }
            comments_array[quan_struct].comment_data = comment_text;
            quan_struct++;
        }
    }
    html_generator(comments_array, path, quan_struct);
    printf("%s%s\n", "Succsesfully created documentation to file by ", path);
    return 0;
}