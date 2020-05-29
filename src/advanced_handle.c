#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/********************************************************************
 * Creates a unique file name which takes
 * the name, day, number and time of creation of the documentation
 ********************************************************************/
char* Generate_filename(char* path, char* dest_dir)
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
    size_t len = strlen(str_time) - 1;
    if (str_time[len] == '\n') {
        str_time[len] = '\0';
    }
    int max_time_len = 50;
    char* filename = (char*)calloc((strlen(path) + max_time_len), sizeof(char));
    sprintf(filename,
            "%s%s%s%s%s%s",
            dest_dir,
            "/",
            Get_filename_without_extension(path),
            "_",
            str_time,
            ".html");
    return filename;
}
/********************************************************************
 * This funtion reterned description to type of document, which will be written
 * to the html page header
 ********************************************************************/
char* Get_document_type(char* path)
{
    char* extension = Get_file_extension(path);
    if (!strcmp(extension, "h")) {
        return "<i>Header file to program code on C/C++</i></br></br>";
    } else if (!strcmp(extension, "c")) {
        return "<i>Program code in language C</i></br></br>";
    } else if (!strcmp(extension, "cpp")) {
        return "<i>Program code in language C++</i></br></br>";
    }
    return "";
}
