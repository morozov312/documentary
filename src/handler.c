#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len_inp_str 500
char* expansion_handle(char* str)
{
    int max_len_expan = 4;
    char* expantion = (char*)calloc(max_len_expan, sizeof(char));
    unsigned int len_path = strlen(str);
    int j = 0;
    for (int i = len_path - 1; i != 0; i--) {
        expantion[j] = str[i];
        j++;
        if (str[i - 1] == '.' || j == 3) {
            break;
        }
    }
    int exp_temp_len = strlen(expantion);
    char* reversed_str = (char*)calloc(exp_temp_len, sizeof(char));
    char buff;
    int k = 0;
    for (int i = exp_temp_len - 1; i >= 0; i--) {
        buff = expantion[i];
        reversed_str[k] = buff;
        k++;
    }
    return reversed_str;
}

char* filename_without_expan(char* path)
{
    int last_slash_index;
    int last_dot_index;
    for (unsigned int i = 0; i < strlen(path); i++) {
        if (path[i] == '/') {
            last_slash_index = i;
        } else if (path[i] == '.') {
            last_dot_index = i;
        }
    }
    int len_of_filename = last_dot_index - last_slash_index;
    char* filename = (char*)malloc(len_of_filename * sizeof(char));
    int counter = 0;
    for (unsigned int i = last_slash_index + 1; i < last_dot_index; i++) {
        filename[counter] = path[i];
        counter++;
    }
    if (strlen(filename) <= 1) {
        return 0;
    } else {
        return filename;
    }
}

int bracket_check(char* str)
{
    int symbol_counter = 0;
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] == '{' || str[i] == '}' || str[i] == ' ') {
            continue;
        } else {
            symbol_counter++;
        }
    }
    if (symbol_counter != 0) {
        return 0;
    } else {
        return 1;
    }
}

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

char* code_from_string_with_comment(char* str)
{
    int last_index_slash;
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] == '/' && str[i - 1] == '/') {
            last_index_slash = i - 1;
        }
    }
    char* code_string = (char*)calloc(last_index_slash * sizeof(char));
    for (int i = 0; i < last_index_slash - 1; i++) {
        code_string[i] = str[i];
    }
    return code_string;
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
        quan_str++;
        temp = (char*)malloc(max_len_inp_str * sizeof(char));
        ptrFile = fgets(temp, max_len_inp_str, myfile);
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
int single_comment_check(char* str)
{
    int len = strlen(str);
    int flag = 0;
    for (int i = 0; i < len; i++) {
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
int muitiline_comment_begin_check(char* str)
{
    int len = strlen(str);
    int flag = 0;
    for (int i = 0; i < len; i++) {
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
int muitiline_comment_end_check(char* str)
{
    unsigned int len = strlen(str);
    int flag = 0;
    for (int i = 0; i < len; i++) {
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
        if (strlen(temp) == 0) {
            continue;
        }
        data[quan_str] = temp;
        quan_str++;
    }
    fclose(myfile);
    return data;
}
