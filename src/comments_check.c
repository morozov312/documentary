#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int single_comment_check(char* str)
{
    unsigned int len = strlen(str);
    int flag = 0;
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '/' && str[i + 1] == '/') {
            flag++;
            i++;
        }
    }
    return flag > 0 ? 1 : 0;
}

// This function checks multiline comment's begin
int multiline_comment_begin_check(char* str)
{
    unsigned int len = strlen(str);
    int flag = 0; // can be rewritten
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '/' && str[i + 1] == '*') {
            flag++;
        }
    }
    return flag > 0 ? 1 : 0;
}
// This function checks multiline comment's end
int multiline_comment_end_check(char* str)
{
    unsigned int len = strlen(str);
    int flag = 0;
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == '*' && str[i + 1] == '/') {
            flag++;
        }
    }
    return flag > 0 ? 1 : 0;
}