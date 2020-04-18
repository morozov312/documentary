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
    int exp_thrid = -1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_third, exp_thrid);
}
CTEST(handle, mult_comment_check_b)
{
    // Given
    char str_first[] = " not comment /* comment";
    char str_second[] = " not comment";
    char str_thrid[] = " not comment /* comment /* nested comment";
    // When
    int res_first = muitiline_comment_begin_check(str_first);
    int res_second = muitiline_comment_begin_check(str_second);
    int res_thrid = muitiline_comment_begin_check(str_thrid);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_thrid = -1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_thrid, exp_thrid);
}
CTEST(handle, mult_comment_check_e)
{
    // Given
    char str_first[] = " comment */ not comment";
    char str_second[] = " not comment";
    char str_thrid[] = "  comment */ not comment */ nested comment";
    // When
    int res_first = muitiline_comment_end_check(str_first);
    int res_second = muitiline_comment_end_check(str_second);
    int res_thrid = muitiline_comment_end_check(str_thrid);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_thrid = -1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_thrid, exp_thrid);
}
CTEST(handle, expansion_handler)
{
    // Given
    const char str_first[] = "handler.h";
    const char str_second[] = ".h";
    const char str_third[] = "src/main.cpp";
    // When
    char* res_first = expansion_handle(str_first);
    char* res_second = expansion_handle(str_second);
    char* res_third = expansion_handle(str_third);
    // Then
    const char exception_first[] = "h";
    const char exception_second[] = "h";
    const char exception_third[] = "cpp";
    ASSERT_STR(exception_first, res_first);
    ASSERT_STR(exception_second, res_second);
    ASSERT_STR(exception_third, res_third);
}
CTEST(handle, expantion_check)
{
    // Given
    const char str_first[] = "./myprogram/main.cpp";
    const char str_second[] = "./src/grab.h";
    const char str_third[] = "nothing";
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