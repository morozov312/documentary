#include "utilities.h"
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
