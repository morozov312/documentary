#include "comments_delete.h"
#include <ctest.h>

CTEST(comments_delete, del_multiline_comment_stars)
{
    // Given
    char str_first[] = " * comment ";
    char str_second[] = " comment without stars";
    char str_third[] = " * comment withs star and pointer *";
    char str_fourth[] = "int * ptr = NULL";
    char str_fifth[] = "/****************";
    // When
    char* res_first = del_multiline_comment_stars(str_first);
    char* res_second = del_multiline_comment_stars(str_second);
    char* res_third = del_multiline_comment_stars(str_third);
    char* res_fourth = del_multiline_comment_stars(str_fourth);
    char* res_fifth = del_multiline_comment_stars(str_fifth);
    // Then
    char exp_first[] = "   comment ";
    char exp_second[] = " comment without stars";
    char exp_thrid[] = "   comment withs star and pointer *";
    char exp_fourth[] = "int * ptr = NULL";
    char exp_fifth[] = "/****************";
    ASSERT_STR(res_first, exp_first);
    ASSERT_STR(res_second, exp_second);
    ASSERT_STR(res_third, exp_thrid);
    ASSERT_STR(res_fourth, exp_fourth);
    ASSERT_STR(res_fifth, exp_fifth); // this case added after bug fixed
}
CTEST(comments_delete, del_multiline_comment_begin)
{
    // Given
    char str_first[] = " /* comment begin ";
    char str_second[] = " not comment";
    char str_third[] = " /* comment  /* nested";
    char str_fourth[] = "/* comment */";
    // When
    char* res_first = del_multiline_comment_begin(str_first);
    char* res_second = del_multiline_comment_begin(str_second);
    char* res_third = del_multiline_comment_begin(str_third);
    char* res_fourth = del_multiline_comment_begin(str_fourth);
    // Then
    char exp_first[] = "    comment begin ";
    char exp_second[] = " not comment";
    ;
    char exp_thrid[] = "    comment     nested";
    char exp_fourth[] = "   comment */";
    ASSERT_STR(res_first, exp_first);
    ASSERT_STR(res_second, exp_second);
    ASSERT_STR(res_third, exp_thrid);
    ASSERT_STR(res_fourth, exp_fourth);
}
CTEST(comments_delete, del_multiline_comment_end)
{
    // Given
    char str_first[] = "comment end */";
    char str_second[] = " not comment";
    char str_third[] = " comment end */ nested */";
    char str_fourth[] = "/* comment */";
    // When
    char* res_first = del_multiline_comment_end(str_first);
    char* res_second = del_multiline_comment_end(str_second);
    char* res_third = del_multiline_comment_end(str_third);
    char* res_fourth = del_multiline_comment_end(str_fourth);
    // Then
    char exp_first[] = "comment end   ";
    char exp_second[] = " not comment";
    char exp_thrid[] = " comment end    nested   ";
    char exp_fourth[] = "/* comment   ";
    ASSERT_STR(res_first, exp_first);
    ASSERT_STR(res_second, exp_second);
    ASSERT_STR(res_third, exp_thrid);
    ASSERT_STR(res_fourth, exp_fourth);
}
CTEST(comments_delete, del_documentary_comment_symbols)
{
    // Given
    char str_first[] = "/** *comment end ";
    char str_second[] = "/*! not comment";
    char str_third[] = "/**comment";
    // When
    char* res_first = del_documentary_comment_symbols(str_first);
    char* res_second = del_documentary_comment_symbols(str_second);
    char* res_third = del_documentary_comment_symbols(str_third);
    // Then
    char exp_first[] = " *comment end ";
    char exp_second[] = " not comment";
    char exp_third[] = "comment";
    ASSERT_STR(exp_first, res_first);
    ASSERT_STR(exp_second, res_second);
    ASSERT_STR(exp_third, res_third);
}