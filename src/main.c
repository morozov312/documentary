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

#include "documentary.h"
#include "handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNT_OF_FILES 10

int main(int argc, char* argv[])
{
    if (argc != 5 && argc != 3) {
        printf("%s\n", "error");
        return 0;
    }
    char* start_folder = get_inpdir(argc, argv);
    char** paths_array = (char**)calloc(MAX_COUNT_OF_FILES, sizeof(char*));
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        paths_array[i] = (char*)calloc(255, sizeof(char));
    }
    recursive_files_search(start_folder, paths_array);
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        // printf("%s\n", paths_array[i]); // here was starting documente
        // creation
        unsigned int len = strlen(paths_array[i]);
        // need develop func witch del invis files
        if (len > 0) {
            document_creation(paths_array[i]);
        }
    }
    for (int i = 0; i < MAX_COUNT_OF_FILES; i++) {
        free(paths_array[i]);
    }
    free(paths_array);
    return 0;
}