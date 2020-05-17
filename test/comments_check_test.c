#include "comments_check.h"
#include <ctest.h>

CTEST(comments_check, check_single_comment)
{
    // Given
    char str_first[] = " not comment // comment";
    /// comment
    char str_second[] = " not comment";
    char str_third[] = " not comment // comment // nested comment";
    // When
    int res_first = check_single_comment(str_first);
    int res_second = check_single_comment(str_second);
    int res_third = check_single_comment(str_third);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_third = 1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_third, exp_third);
}
CTEST(comments_check, check_multiline_comment_begin)
{
    // Given
    char str_first[] = " not comment /* comment";
    char str_second[] = " not comment";
    char str_third[] = " not comment /* comment /* nested comment";
    // When
    int res_first = check_multiline_comment_begin(str_first);
    int res_second = check_multiline_comment_begin(str_second);
    int res_thrid = check_multiline_comment_begin(str_third);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_third = 1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_thrid, exp_third);
}
CTEST(comments_check, check_multiline_comment_end)
{
    // Given
    char str_first[] = " comment */ not comment";
    char str_second[] = " not comment";
    char str_third[] = "  comment */ nested comment */ not comment";
    // When
    int res_first = check_multiline_comment_end(str_first);
    int res_second = check_multiline_comment_end(str_second);
    int res_third = check_multiline_comment_end(str_third);
    // Then
    int exp_first = 1;
    int exp_second = 0;
    int exp_third = 1;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_third, exp_third);
}