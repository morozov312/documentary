#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* expansion_handle(char str[])
{
    int max_len_expan = 4;
    char* expantion = (char*)malloc(max_len_expan * sizeof(char));
    return expantion;
}
int expan_check(char filepath[])
{
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
    const int max_len_inp_str = 1000;
    const int max_quan_str = 100;
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
        int inp_str_len = strlen(temp) + 1;
        for (int i = 0; i < inp_str_len; i++) {
            if (temp[i] == '\n') {
                temp[i] = '\0';
            }
        }
        int check = expan_check(expansion_handle(temp));
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
int single_comment_check(char str[])
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
        return 0;
    }
    return 0;
}
int muitiline_comment_begin_check(char str[])
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
        return 0;
    }
    return 0;
}
int muitiline_comment_end_check(char str[])
{
    int len = strlen(str);
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
        return 0;
    }
    return 0;
}
int document_handle(char** paths)
{
    int quan_of_paths = sizeof(paths) / sizeof(paths[0]);
    for (int i = 0; i < quan_of_paths; i++) {
        FILE* myfile;
        myfile = fopen(paths[i], "r");
        if (myfile == NULL) {
            printf("%s%s%s\n", "On path ", paths[i], " file not found!");
            return 0;
        }
        char *temp, *ptrFile;
        const int max_len_inp_str = 1000;
        const int max_quan_str = 100 * 1000;
        int quan_str = 0;
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
            printf("%s\n", temp);
        }
        fclose(myfile);
    }
    return 0;
}
