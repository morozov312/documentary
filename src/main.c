#include "documentary.h"
#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char path[] = "./path/path.txt";
    const int max_len_inp_str = 1000;
    const int max_quan_str = 10000;
    char** paths = (char**)malloc(max_quan_str * sizeof(char*));
    for (int i = 0; i < max_quan_str; i++) {
        paths[i] = (char*)malloc(max_len_inp_str * sizeof(char));
    }
    for (int i = 0; i < max_quan_str; i++) {
        for (int j = 0; j < max_len_inp_str; j++) {
            paths[i][j] = 0;
        }
    }
    paths = path_reading(path, paths);
    int quan_of_paths = sizeof(paths) / sizeof(paths[0]);
    char** file_data;
    for (int i = 0; i < quan_of_paths; i++) {
        file_data = document_handle(paths[i]);
        // html
    }
    for (int i = 0; i < max_quan_str; i++) {
        free(paths[i]);
    }
    free(paths);
    return 0;
}