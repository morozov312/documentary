#include "utilities.h"
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(utilities, exclude_html)
{
    // Given
    const char first[] = "<<<>>>";
    const char second[] = "int n = 10";
    char* str_first = (char*)malloc(strlen(first) * sizeof(char));
    char* str_second = (char*)malloc(strlen(second) * sizeof(char));
    strcpy(str_first, first);
    strcpy(str_second, second);
    // When
    char* res_first = exclude_html(str_first);
    char* res_second = exclude_html(str_second);
    // Then
    char* exception_first = "&lt&lt&lt&gt&gt&gt";
    char* exception_second = "int n = 10";
    ASSERT_STR(exception_first, res_first);
    ASSERT_STR(exception_second, res_second);
    free(res_first);
    free(res_second);
}
CTEST(utilities, filename_without_extension)
{
    // Given
    char str_first[] = "./myprogram/main.cpp";
    char str_second[] = "./src/grab.h";
    char str_third[] = "nothing";
    // When
    char* res_first = filename_without_extension(str_first);
    char* res_second = filename_without_extension(str_second);
    char* res_third = filename_without_extension(str_third);
    // Then
    char* exception_first = "main";
    char* exception_second = "grab";
    char* exception_third = "";
    ASSERT_STR(exception_first, res_first);
    ASSERT_STR(exception_second, res_second);
    ASSERT_STR(exception_third, res_third);
}
CTEST(utilities, get_inpdir)
{
    // Given
    char* argv_first[] = {"./documentary ", "-inpdir", "./src"};
    char* argv_second[] = {"./documentary ", "-inpdir", "-inpdir"};
    char* argv_third[] = {"./documentary ", "-l", "./src"};
    int qty_for_three = 3;
    // When
    char* res_fisrt = get_inpdir(qty_for_three, argv_first);
    char* res_second = get_inpdir(qty_for_three, argv_second);
    char* res_thrid = get_inpdir(qty_for_three, argv_third);
    // Then
    char* exception_first = "./src";
    char* exception_second = "-inpdir";
    char* exception_third = "";
    ASSERT_STR(exception_first, res_fisrt);
    ASSERT_STR(exception_second, res_second);
    ASSERT_STR(exception_third, res_thrid);
}
CTEST(utilities, get_outdir)
{
    // Given
    char* argv_first[] = {"./documentary ", "-outdir", "./docs"};
    char* argv_second[] = {"./documentary ", "-outdir", "-outdir"};
    char* argv_third[] = {"./documentary ", "-l", "./src"};
    int qty_for_three = 3;
    // When
    char* res_fisrt = get_outdir(qty_for_three, argv_first);
    char* res_second = get_outdir(qty_for_three, argv_second);
    char* res_thrid = get_outdir(qty_for_three, argv_third);
    // Then
    char* exception_first = "./docs";
    char* exception_second = "-outdir";
    char* exception_third = "./docs";
    ASSERT_STR(exception_first, res_fisrt);
    ASSERT_STR(exception_second, res_second);
    ASSERT_STR(exception_third, res_thrid);
}
CTEST(utilities, get_data_from_document)
{
    // Given
    char str_first[] = "./test/main.c";
    char str_second[] = "./test/main.cpp";
    // When
    char** res_first = get_data_from_document(str_first);
    char** res_second = get_data_from_document(str_second);
    // Then
    char* exception_fisrt = "#define CTEST_MAIN\n";
    ASSERT_STR(res_first[0], exception_fisrt);
    ASSERT_NULL(res_second);
}