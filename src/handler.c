#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3
char* expansion_handle(char str[]) // need testuing
{
    int max_len_expan = 4;
    char* temp = (char*)malloc(max_len_expan * sizeof(char));
    int counter = 0;
    for (int i = 1; str[i] != '\0'; i++) { // need fixed
        if (str[i] == '.') {
            counter++;
            unsigned long int j = 0;
            int k = i + 1;
            while (j <= strlen(temp)) {
                temp[j] = str[k];
                k++;
                j++;
            }
        }
    }
    if (counter == 1) {
        return temp;
    } else {
        return 0;
    }
}
int expan_check(char str[]) // need testing
{
    int bool = 0;
    // doing code
    if (bool) {
        return 0;
    } else {
        return 1;
    }
    return 0;
}
char** path_reading(char path[], char** paths)
{
    FILE* myfile;
    myfile = fopen(path, "r");
    if (myfile == NULL) {
        printf("File path.txt not found!");
        return 0;
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
int single_comment_check()
{
    // doing code,if str have single comment return 1
    // if have a nested comments printf error
    // need testing
    return 0;
}
int muitiline_comment_begin_check()
{
    // doing code
    // need testing
    return 0;
}
int muitiline_comment_end_check()
{
    // doing code
    // need testing
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
        const int max_len_inp_str = 100 * 1000;
        const int max_quan_str = 1000 * 1000;
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
