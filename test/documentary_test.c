#include <ctest.h>
#include <documentary.h>
CTEST(documentary, single_comment_deletion)
{
    // Given
    const char str_first[] = "//// comment";
    const char str_second[] = "// comment";
    const char str_third[] = "/// comment";
    // When
    char* res_first = del_single_comment(str_first);
    char* res_second = del_single_comment(str_second);
    char* res_third = del_single_comment(str_third);
    // Then
    const char exception_first[] = "  // comment";
    const char exception_second[] = "   comment";
    const char exception_third[] = "  / comment";
    ASSERT_STR(exception_first, res_first);
    ASSERT_STR(exception_second, res_second);
    ASSERT_STR(exception_third, res_third);
}
CTEST(documentary, del_multiline_comment_stars)
{
    // Given
    char str_first[] = " * comment ";
    char str_second[] = " comment without stars";
    char str_third[] = " * comment withs star and pointer *";
    char str_fourth[] = "int * ptr = NULL";
    // When
    char* res_first = del_multiline_comment_stars(str_first);
    char* res_second = del_multiline_comment_stars(str_second);
    char* res_third = del_multiline_comment_stars(str_third);
    char* res_fourth = del_multiline_comment_stars(str_third);
    // Then
    char exp_first[] = "   comment ";
    char exp_second[] = " comment without stars";
    char exp_thrid[] = "   comment withs star and pointer *";
    char exp_fourth[] = "int * ptr = NULL";
    ASSERT_STR(res_first, exp_first);
    ASSERT_STR(res_second, exp_second);
    ASSERT_STR(res_third, exp_thrid);
    ASSERT_STR(res_third, exp_thrid);
}
