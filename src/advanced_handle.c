#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*! creates a unique file name which takes
 * the name, day, number and time of creation of the documentation */
char* file_name_generator(char* path)
{
    long int s_time = 0;
    struct tm* m_time;
    s_time = time(NULL);
    m_time = localtime(&s_time);
    char* str_time = asctime(m_time);
    for (int i = 0; str_time[i] != '\0'; i++) {
        if (str_time[i] == ' ') {
            str_time[i] = '_';
        }
    }
    unsigned int len = strlen(str_time) - 1;
    if (str_time[len] == '\n') {
        str_time[len] = '\0';
    }
    char* filename = (char*)calloc((strlen(path) + 30), sizeof(char));
    sprintf(filename,
            "%s%s%s%s%s",
            "./docs/",
            str_time,
            "_",
            filename_without_extension(path),
            ".html");
    return filename;
}

/**********************************************************
 * this function creates an HTML page from the documentation
 * in the directory - documentary/docs/
 **********************************************************/
char* get_document_type(char* path)
{
    char* extension = get_file_extension(path);
    if (!strcmp(extension, "h")) {
        return "<i>Header file to program code on C/C++</i></br></br>";
    } else if (!strcmp(extension, "c")) {
        return "<i>Program code in language C</i></br></br>";
    } else if (!strcmp(extension, "cpp")) {
        return "<i>Program code in language C++</i></br></br>";
    } else {
        return "";
    }
}
