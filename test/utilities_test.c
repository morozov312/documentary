#include "utilities.h"
#include <ctest.h>

// CTEST(utilities, exclude_html)
// {
//     // Given
//     char str_first[] = "<<<>>>";
//     char str_second[] = "int n = 10";
//     // When
//     char* res_first = exclude_html(str_first);
//     char* res_second = exclude_html(str_second);
//     // Then
//     char* exception_first = "&lt&lt&lt&gt&gt&gt";
//     char* exception_second = "int n = 10";
//     ASSERT_STR(exception_first, res_first);
//     ASSERT_STR(exception_second, res_second);
// }

// CTEST(utilities, filename_without_extension)
// {
//     // Given
//     char str_first[] = "./myprogram/main.cpp";
//     char str_second[] = "./src/grab.h";
//     char str_third[] = "nothing";
//     // When
//     char* res_first = filename_without_extension(str_first);
//     char* res_second = filename_without_extension(str_second);
//     char* res_third = filename_without_extension(str_third);
//     // Then
//     char* exception_first = "main";
//     char* exception_second = "grab";
//     char* exception_third = "";
//     ASSERT_STR(exception_first, res_first);
//     ASSERT_STR(exception_second, res_second);
//     ASSERT_STR(exception_third, res_third);
// }

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
    char* exception_third = "";
    ASSERT_STR(exception_first, res_fisrt);
    ASSERT_STR(exception_second, res_second);
    ASSERT_STR(exception_third, res_thrid);
}

CTEST(utilities, check_document_multiline_commentary)
{
    // Given
    char* str_first = "/**   begin";
    char* str_second = "/*!  begin";
    char* str_third = "/* nothing";
    // When
    int res_first = check_document_multiline_commentary(str_first);
    int res_second = check_document_multiline_commentary(str_second);
    int res_third = check_document_multiline_commentary(str_third);
    // Then
    int exception_first = 1;
    int exception_second = 1;
    int exception_third = 0;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
}
CTEST(utilities, check_single_documentary_comment)
{
    // Given
    char* str_first = "///   begin";
    char* str_second = "//!  begin";
    char* str_third = "// nothing";
    // When
    int res_first = check_single_documentary_comment(str_first);
    int res_second = check_single_documentary_comment(str_second);
    int res_third = check_single_documentary_comment(str_third);
    // Then
    int exception_first = 1;
    int exception_second = 1;
    int exception_third = 0;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
}
