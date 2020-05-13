#include "comments_check.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define qty_of_extentions 3

int extension_check(char* filepath)
{
    char* valid_extentions[qty_of_extentions] = {"cpp", "h", "c"};
    int flag = 0;
    char* temp = get_file_extension(filepath);
    for (int i = 0; i < qty_of_extentions; i++) {
        flag = strcmp(temp, valid_extentions[i]);
        if (flag == 0) {
            return 1;
        }
    }
    return 0;
}
// This function checks single comments

int check_single_documentary_comment(char* string)
{
    char* ptr_slash = strchr(string, '/');
    if (single_comment_check(string) == 1) {
        if (ptr_slash[2] == '/' || ptr_slash[2] == '!')
            return 1;
        else
            return 0;
    }
    return 0;
}

int check_document_multiline_commentary(char* string)
{
    char* ptr_first_star = strchr(string, '*');
    if (multiline_comment_begin_check(string) == 1) {
        if ((ptr_first_star)[1] == '*' || (ptr_first_star)[1] == '!') {
            return 1; // valid comment
        } else {
            return 0; // invalid comment
        }
    } else
        return 0;
}
