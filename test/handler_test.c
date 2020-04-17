#include <ctest.h>
#include <handler.h>
CTEST(handle, single_commente_check)
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
    int exp_third = 0;
    ASSERT_EQUAL(res_first, exp_first);
    ASSERT_EQUAL(res_second, exp_second);
    ASSERT_EQUAL(res_third, exp_third);
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