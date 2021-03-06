#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Check_single_comment(char* str)
{
    size_t len = strlen(str);
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '/' && str[i + 1] == '/') {
            return 1;
        }
    }
    return 0;
}
int Check_multiline_comment_begin(char* str)
{
    size_t len = strlen(str);
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '/' && str[i + 1] == '*') {
            return 1;
        }
    }
    return 0;
}
int Check_multiline_comment_end(char* str)
{
    size_t len = strlen(str);
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '*' && str[i + 1] == '/') {
            return 1;
        }
    }
    return 0;
}