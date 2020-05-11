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
    int last_index = 0;
    int temp = 0;
    unsigned int filename_estimate_length = strlen(path);
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
    unsigned int len = strlen(str_time) - 1;
    if (str_time[len] == '\n') {
        str_time[len] = '\0';
    }
    char* temp_filename
            = (char*)calloc((filename_estimate_length + 20), sizeof(char));
    for (unsigned int i = 0; i < filename_estimate_length; i++) {
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
/**********************************************************
 * this function creates an HTML page from the documentation
 * in the directory - documentary/docs/
 **********************************************************/
int html_generator(struct comment* list, char* path, int quan_structs)
{
    FILE* documentary;
    char* name = file_name_generator(path);
    documentary = fopen(name, "w");
    if (documentary == NULL) {
        printf("%s\n", "Error create html page!");
        return 0;
    }
    // ==========================================================================
    // Header
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
    // document programming language definition
    char* expansion;
    // = expansion_handle(path);
    if (!strcmp(expansion, "h")) {
        fputs("<i>Header file to program code on C/C++</i></br></br>",
              documentary);
    }
    if (!strcmp(expansion, "c")) {
        fputs("<i>Program code in language C</i></br></br>", documentary);
    }
    if (!strcmp(expansion, "cpp")) {
        fputs("<i>Program code in language C++</i></br></br>", documentary);
    }
    fputs("<b>Warning</b></br></br><i>This documentation is based on the "
          "program code containing </br> ",
          documentary);
    // ==========================================================================
    // main content
    for (int i = 0; i < quan_structs; i++) {
        if (strlen(list[i].comment_data)) {
            fputs("<p class=\"comment\">", documentary);
            fputs(list[i].comment_data, documentary);
            fputs("</br>", documentary);
            fputs("</p>", documentary);
        }
        if (strlen(list[i].code_string)) {
            fputs("<code>", documentary);
            fputs(list[i].code_string, documentary);
            fputs("</code></br></br>", documentary);
        }
    }
    // ==========================================================================
    // Footer
    fputs("</div></body></html>", documentary);
    fclose(documentary);
    return 1;
}
