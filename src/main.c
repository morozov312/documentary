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
int main(int argc, char* argv[])
{
    if (argc != 5 && argc != 3) {
        printf("%s\n", "error");
        return 0;
    }
    char* inp = get_inpdir(argc, argv);
    return 0;
}