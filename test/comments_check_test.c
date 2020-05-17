#include "comments_check.h"
#include <ctest.h>

CTEST(comments_check, single_comment_check)
{
    // Given
    char str_first[] = " not comment // comment";
    /// comment
    char str_second[] = " not comment";
    char str_third[] = " not comment // comment // nested comment";
    // When
    int res_first = single_comment_check(str_first);
    int res_second = single_comment_check(str_second);
    int res_third = single_comment_check(str_third);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_third = 1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_third, exp_third);
}
CTEST(comments_check, mult_comment_begin_check)
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
    int exp_third = 1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_thrid, exp_third);
}
CTEST(comments_check, mult_comment_end_check)
{
    // Given
    char str_first[] = " comment */ not comment";
    char str_second[] = " not comment";
    char str_third[] = "  comment */ nested comment */ not comment";
    // When
    int res_first = multiline_comment_end_check(str_first);
    int res_second = multiline_comment_end_check(str_second);
    int res_third = multiline_comment_end_check(str_third);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_third = 1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_third, exp_third);
}