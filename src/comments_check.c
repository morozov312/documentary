#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_single_comment(char* str)
{
    unsigned int len = strlen(str);
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '/' && str[i + 1] == '/') {
            return 1;
        }
    }
    return 0;
}
int check_multiline_comment_begin(char* str)
{
    unsigned int len = strlen(str);
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '/' && str[i + 1] == '*') {
            return 1;
        }
    }
    return 0;
}
int check_multiline_comment_end(char* str)
{
    unsigned int len = strlen(str);
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '*' && str[i + 1] == '/') {
            return 1;
        }
    }
    return 0;
}