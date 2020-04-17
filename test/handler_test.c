#include <ctest.h>
#include <handler.h>
CTEST(handle, single_comment_check)
{
    // Given
    char str_first[] = " not comment // comment";
    char str_second[] = " not comment";
    char str_thrid[] = " not comment // comment // nested comment";
    // When
    int res_first = single_comment_check(str_first);
    int res_second = single_comment_check(str_second);
    int res_thrid = single_comment_check(str_thrid);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_thrid = 0;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_thrid, exp_thrid);
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
    int exp_thrid = 0;
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
    int exp_thrid = 0;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_thrid, exp_thrid);
}