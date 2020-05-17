#include "advanced_handle.h"
#include <ctest.h>

CTEST(advanced_handle, get_document_type)
{
    // Given
    char str_first[] = "./folder/src/main.cpp";
    char str_second[] = "./src/header.h";
    char str_third[] = "./fake/depth.c";
    char str_fourth[] = "./fake/main.py";
    // When
    char* res_first = get_document_type(str_first);
    char* res_second = get_document_type(str_second);
    char* res_third = get_document_type(str_third);
    char* res_fourth = get_document_type(str_fourth);
    // Then
    char exp_first[] = "<i>Program code in language C++</i></br></br>";
    char exp_second[] = "<i>Header file to program code on C/C++</i></br></br>";
    char exp_third[] = "<i>Program code in language C</i></br></br>";
    char exp_fourth[] = "";
    ASSERT_STR(exp_first, res_first);
    ASSERT_STR(exp_second, res_second);
    ASSERT_STR(exp_third, res_third);
    ASSERT_STR(exp_fourth, res_fourth);
}
