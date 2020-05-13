#include "advanced_check.h"
#include <ctest.h>

CTEST(advanced_check, document_handle)
{
    // Given
    char str[] = "./test/main.c";
    // When
    char** res_first = get_data_from_document(str);
    // Then
    char* res_fisrt = "#define CTEST_MAIN\n";
    ASSERT_STR(res_first[0], res_fisrt);
}
CTEST(advanced_check, extension_check)
{
    // Given
    char str_first[] = "./myprogram/main.cpp";
    char str_second[] = "./src/grab.h";
    char str_third[] = "nothing";
    // When
    int res_first = extension_check(str_first);
    int res_second = extension_check(str_second);
    int res_third = extension_check(str_third);
    // Then
    int exception_first = 1;
    int exception_second = 1;
    int exception_third = 0;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
}
