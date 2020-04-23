#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len_inp_str 500
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
    return reversed_str;
}
// This function checks lines with code and multiline comments
int code_and_multiline_comment_check(char* str)
{
    unsigned int lengh = strlen(str);
    int begin_index, end_index;

    for (unsigned int i = 1; i < lengh; i++) {
        if (str[i] == '*' && str[i - 1] == '/') {
            begin_index = i - 1;
        } else if (str[i] == '/' && str[i - 1] == '*') {
            end_index = i;
        }
    }
    for (int i = 0; i < begin_index - 1; i++) {
        if (str[i] != ' ') {
            return 1;
        }
    }
    for (unsigned int i = end_index + 1; i < lengh; i++) {
        if (str[i] != ' ') {
            return 1;
        }
    }
    return 0;
}
// This functiob handles filename deleting expansion
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
    char* filename = (char*)malloc(len_of_filename * sizeof(char));
    int counter = 0;
    for (unsigned int i = last_slash_index + 1; i < last_dot_index; i++) {
        filename[counter] = path[i];
        counter++;
    }
    if (strlen(filename) < 1) {
        return 0;
    } else {
        return filename;
    }
}
// This function checks comments on their type
int single_comment_code_check(char* str)
{
    int symbol_counter = 0;
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] == '/' && str[i + 1] == '/') {
            break;
        } else if (str[i] == ' ') {
            continue;
        } else {
            symbol_counter++;
        }
    }
    if (symbol_counter != 0) {
        return 1;
    } else {
        return 0;
    }
}
// This function returns code if there are code in line with comment
char* code_from_string_with_comment(char* str)
{
    unsigned int last_index_slash = 0;
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] == '/' && str[i - 1] == '/') {
            last_index_slash = i - 1;
        }
    }
    char* code_string = (char*)calloc(last_index_slash, sizeof(char));
    for (unsigned int i = 0; i < last_index_slash; i++) {
        code_string[i] = str[i];
    }
    return code_string;
}
// This function checks file's expansion
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
// This function return comments from line with code
char* comment_from_string_with_code(char* str)
{
    unsigned int first_double_slash_index = 0;
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] == '/' && str[i - 1] == '/') {
            first_double_slash_index = i - 1;
            break;
        }
    }
    unsigned int max_len_of_comment = strlen(str) - first_double_slash_index;
    char* comment_string = (char*)calloc(max_len_of_comment, sizeof(char));
    int counter = 0;
    for (unsigned int i = first_double_slash_index; i < strlen(str); i++) {
        comment_string[counter] = str[i];
        counter++;
    }
    return comment_string;
}
// This function checks comment on separator
int comment_separator_check(char* str)
{
    int counter_of_same_symbols = 0;
    for (unsigned int i = 1; i < strlen(str); i++) {
        if (str[i] == '/' && str[i - 1] == '/') {
            for (unsigned int j = i + 1; j < strlen(str); j++) {
                if (str[j] == str[j - 1]) {
                    counter_of_same_symbols++;
                }
            }
            break;
        }
    }
    if (counter_of_same_symbols > (int)(strlen(str) / 3)) {
        return 1; // string is separator comment
    } else {
        return 0; // string is not separator comment
    }
}
// This function reads array of pathes
char** path_reading(char path[], char** paths)
{
    FILE* myfile;
    myfile = fopen(path, "r");
    if (myfile == NULL) {
        printf("File path.txt not found!");
        return paths;
    }
    char *temp, *ptrFile;
    const int max_quan_str = 10;
    int quan_str = 0;
    int num_valid_path = 0;
    while (quan_str < max_quan_str) {
        temp = (char*)calloc(max_len_inp_str, sizeof(char));
        ptrFile = fgets(temp, max_len_inp_str, myfile);
        quan_str++;
        if (ptrFile == NULL) {
            if (feof(myfile) != 0) {
                break;
            } else {
                continue;
            }
        }
        unsigned int len = strlen(temp) - 1;
        if (temp[len] == '\n') {
            temp[len] = '\0';
        }
        if (len == 0) {
            continue;
        }
        // the ability to add comments
        if (temp[0] == '#') {
            continue;
        }
        int check = expan_check(temp);
        if (check) {
            paths[num_valid_path] = temp;
            num_valid_path++;
        } else {
            printf("%s%s\n", "Error, unsupported format file on ", temp);
            continue;
        }
    }
    fclose(myfile);
    return paths;
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
    const int max_quan_str = 50 * 1000;
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
