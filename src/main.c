#include "documentary.h"
#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len_inp_str 500
#define max_quan_str 10
int main()
{
    char path[] = "./path/path.txt";
    char** paths = (char**)calloc(max_quan_str, sizeof(char*));
    for (int i = 0; i < max_quan_str; i++) {
        paths[i] = (char*)calloc(max_len_inp_str, sizeof(char));
    }
    paths = path_reading(path, paths);
    int quan_of_paths = 0;
    for (int i = 0; i < max_quan_str; i++) {
        if (strlen(paths[i]) != 0) {
            quan_of_paths++;
        }
    }
    char** file_data;
    for (int i = 0; i < quan_of_paths; i++) {
        file_data = document_handle(paths[i]);
        if (file_data == 0) {
            continue;
        }
        docs_gen(file_data, paths[i]);
    }
    return 0;
}