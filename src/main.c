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

#include "processing.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNT_OF_ARGS 5
#define MIN_COUNT_OF_ARGS 3
#define MAX_PATH_LEN 255
#define MAX_COUNT_OF_FILES 30

int main(int argc, char* argv[])
{
    if (argc != MAX_COUNT_OF_ARGS && argc != MIN_COUNT_OF_ARGS) {
        printf("%s\n", "Error! Invalid number of arguments");
        return 0;
    }
    char* start_dir = get_inpdir(argc, argv);
    char* dest_dir = get_outdir(argc, argv);
    char** paths_array = (char**)calloc(MAX_COUNT_OF_FILES, sizeof(char*));
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        paths_array[i] = (char*)calloc(MAX_PATH_LEN, sizeof(char));
    }
    recursive_files_search(start_dir, paths_array);
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        unsigned int len = strlen(paths_array[i]);
        if (len > 0) {
            document_creation(paths_array[i], dest_dir);
        }
    }
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        free(paths_array[i]);
    }
    free(paths_array);
    return 0;
}