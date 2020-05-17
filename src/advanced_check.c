#include "comments_check.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTY_OF_EXTENSION 3

int check_extension(char* path)
{
    char* valid_extentions[QTY_OF_EXTENSION] = {"cpp", "h", "c"};
    char* temp = get_file_extension(path);
    for (int i = 0; i < QTY_OF_EXTENSION; i++) {
        if (strcmp(temp, valid_extentions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
int check_single_documentary_comment(char* str)
{
    char* ptr_slash = strchr(str, '/');
    if (check_single_comment(str) == 1) {
        if (ptr_slash[2] == '/' || ptr_slash[2] == '!') {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
int check_multiline_documentary_comment(char* str)
{
    char* ptr_first_star = strchr(str, '*');
    if (check_multiline_comment_begin(str) == 1) {
        if ((ptr_first_star)[1] == '*' || (ptr_first_star)[1] == '!') {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
