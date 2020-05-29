/***************************************
 * THIS PROGRAM GENERATES DOCUMENTARY
 * BY ANALIZING AND REWRITING COMMENTS FROM
 * YOUR FILE TO NEW .html file
 * PROGRAM DEVELOPED BY
 * @MOSKALT AND @MOROZOV312
 *          2020
 * THIS PROGRAMM IS OPENSOURCE PROJECT
 * https://github.com/morozov312/documentary
 ****************************************/

#include "macro.h"
#include "processing.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    char* start_dir;
    char* dest_dir;
    int argc_flag = Check_argc(argc);
    if (!argc_flag) {
        return 0;
    }
    int argv_flag = Check_argv(argc, argv, &start_dir, &dest_dir);
    if (!argv_flag) {
        return 0;
    }
    if (strcmp(start_dir, "") == 0) {
        printf("\x1b[31m Error! \x1b[0m Wrong source directory\n");
        return 0;
    }
    char** paths_array = (char**)calloc(MAX_COUNT_OF_FILES, sizeof(char*));
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        paths_array[i] = (char*)calloc(MAX_PATH_LEN, sizeof(char));
    }
    int recursive_exit_flag = 0;
    int recursive_res = Search_files_recursive(
            start_dir, paths_array, &recursive_exit_flag);
    if (recursive_res == -1) {
        printf("%s\n",
               "\x1b[36mWarning!\x1b[0m limit of files for this "
               "folder "
               "overpassed!");
    }
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        size_t len = strlen(paths_array[i]);
        if (len > 0) {
            Create_document(paths_array[i], dest_dir);
        }
    }
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        free(paths_array[i]);
    }
    free(paths_array);
    return 0;
}