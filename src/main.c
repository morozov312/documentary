#include "documentary.h"
#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char path[] = "./path/path.txt";
    const int max_len_inp_str = 1000;
    const int max_quan_str = 100;
    char** paths = (char**)malloc(max_quan_str * sizeof(char*));
    for (int k = 0; k < max_quan_str; k++) {
        paths[k] = (char*)malloc(max_len_inp_str * sizeof(char));
    }
    for (int i = 0; i < max_quan_str; i++) {
        for (int j = 0; j < max_len_inp_str; j++) {
            paths[i][j] = 0;
        }
    }
    paths = path_reading(path, paths);
    return 0;
}
