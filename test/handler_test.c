#include <ctest.h>
#include <handler.h>
CTEST(handle, single_comment_check)
{
    // Given
    char str_first[] = " not comment // comment";
    char str_second[] = " not comment";
    char str_third[] = " not comment // comment // nested comment";
    // When
    int res_first = single_comment_check(str_first);
    int res_second = single_comment_check(str_second);
    int res_third = single_comment_check(str_third);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_third = -1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_third, exp_third);
}
CTEST(handle, mult_comment_check_b)
{
    // Given
    char str_first[] = " not comment /* comment";
    char str_second[] = " not comment";
    char str_third[] = " not comment /* comment /* nested comment";
    // When
    int res_first = multiline_comment_begin_check(str_first);
    int res_second = multiline_comment_begin_check(str_second);
    int res_thrid = multiline_comment_begin_check(str_third);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_third = -1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_thrid, exp_third);
}
CTEST(handle, mult_comment_check_e)
{
    // Given
    char str_first[] = " comment */ not comment";
    char str_second[] = " not comment";
    char str_third[] = "  comment */ not comment */ nested comment";
    // When
    int res_first = multiline_comment_end_check(str_first);
    int res_second = multiline_comment_end_check(str_second);
    int res_third = multiline_comment_end_check(str_third);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_third = -1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_third, exp_third);
}
CTEST(handle, expansion_handler)
{
    // Given
    char str_first[] = "handler.h";
    char str_second[] = ".h";
    char str_third[] = "src/main.cpp";
    // When
    char* res_first = expansion_handle(str_first);
    char* res_second = expansion_handle(str_second);
    char* res_third = expansion_handle(str_third);
    // Then
    char exception_first[] = "h";
    char exception_second[] = "h";
    char exception_third[] = "cpp";
    ASSERT_STR(exception_first, res_first);
    ASSERT_STR(exception_second, res_second);
    ASSERT_STR(exception_third, res_third);
}
CTEST(handle, expantion_check)
{
    // Given
    char str_first[] = "./myprogram/main.cpp";
    char str_second[] = "./src/grab.h";
    char str_third[] = "nothing";
    // When
    int res_first = expan_check(str_first);
    int res_second = expan_check(str_second);
    int res_third = expan_check(str_third);
    // Then
    int exception_first = 1;
    int exception_second = 1;
    int exception_third = 0;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
}
CTEST(handle, filename_without_expan)
{
    // Given
    char str_first[] = "./myprogram/main.cpp";
    char str_second[] = "./src/grab.h";
    char str_third[] = "nothing";
    // When
    char* res_first = filename_without_expan(str_first);
    char* res_second = filename_without_expan(str_second);
    char* res_third = filename_without_expan(str_third);
    // Then
    char* exception_first = "main";
    char* exception_second = "grab";
    char* exception_third = 0;
    ASSERT_STR(exception_first, res_first);
    ASSERT_STR(exception_second, res_second);
    ASSERT_STR(exception_third, res_third);
}
CTEST(handle, no_html)
{
    // Given
    char str_first[] = "<<<>>>";
    char str_second[] = "int n = 10";
    // When
    char* res_first = no_html(str_first);
    char* res_second = no_html(str_second);
    // Then
    char* exception_first = "&lt&lt&lt&gt&gt&gt";
    char* exception_second = "int n = 10";
    ASSERT_STR(exception_first, res_first);
    ASSERT_STR(exception_second, res_second);
}