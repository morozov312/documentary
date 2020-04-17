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
