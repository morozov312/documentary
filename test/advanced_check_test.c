#include "advanced_check.h"
#include <ctest.h>

CTEST(advanced_Check, Check_extension)
{
    // Given
    char str_first[] = "./myprogram/main.cpp";
    char str_second[] = "./src/grab.h";
    char str_third[] = "nothing";
    // When
    int res_first = Check_extension(str_first);
    int res_second = Check_extension(str_second);
    int res_third = Check_extension(str_third);
    // Then
    int exception_first = 1;
    int exception_second = 1;
    int exception_third = 0;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
}
CTEST(advanced_Check, Check_multiline_documentary_comment)
{
    // Given
    char* str_first = "/**   begin";
    char* str_second = "/*!  begin";
    char* str_third = "/* nothing";
    // When
    int res_first = Check_multiline_documentary_comment(str_first);
    int res_second = Check_multiline_documentary_comment(str_second);
    int res_third = Check_multiline_documentary_comment(str_third);
    // Then
    int exception_first = 1;
    int exception_second = 1;
    int exception_third = 0;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
}
CTEST(advanced_Check, Check_single_documentary_comment)
{
    // Given
    char* str_first = "///   begin";
    char* str_second = "//!  begin";
    char* str_third = "// nothing";
    // When
    int res_first = Check_single_documentary_comment(str_first);
    int res_second = Check_single_documentary_comment(str_second);
    int res_third = Check_single_documentary_comment(str_third);
    // Then
    int exception_first = 1;
    int exception_second = 1;
    int exception_third = 0;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
}