#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int del_single_comment()
{
    // may be on '//' symbols writing ' '
    return 0;
}
int del_multiline_comment_begin()
{
    // may be on '/*' symbols writing ' '
    return 0;
}
int del_multiline_comment_end()
{
    // may be on '*/' symbols writing ' '
    return 0;
}
int del_multiline_comment_stars()
{
    // may be on '*' symbols writing ' '
    // often in multiline comments strings begining with *
    // must be del only first star on string
    return 0;
}
int docs_gen()
{
    // accepts array structs with contain comments and code blocks
    return 0;
}