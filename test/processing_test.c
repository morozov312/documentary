#include "processing.h"
#include <ctest.h>

CTEST(processing, check_code)
{
    // Given
    char str_first[] = "code /// comment";
    char str_second[] = "code /* comment */";
    char str_third[] = "/* begin of comment";
    char str_fourth[] = "int a =0;";
    // When
    int res_first = check_code(str_first);
    int res_second = check_code(str_second);
    int res_third = check_code(str_third);
    int res_fourth = check_code(str_fourth);
    // Then
    int exp_first = 0;
    int exp_second = 0;
    int exp_third = 0;
    int exp_fourth = 1;
    ASSERT_EQUAL(exp_first, res_first);
    ASSERT_EQUAL(exp_second, res_second);
    ASSERT_EQUAL(exp_third, res_third);
    ASSERT_EQUAL(exp_fourth, res_fourth);
}