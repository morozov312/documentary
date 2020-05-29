#include "utilities.h"
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
CTEST(Utilites, Check_argc)
{
    // Given
    int first = 1;
    int second = 10;
    int third = 3;
    int fourth = 5;
    char* arr[] = {"./documentary", "-inpdir", "./src", "-outdir", "./docs"};
    // When
    int res_first = Check_argc(first, arr);
    int res_second = Check_argc(second, arr);
    int res_third = Check_argc(third, arr);
    int res_fourth = Check_argc(fourth, arr);
    // Then
    int exception_first = 0;
    int exception_second = 0;
    int exception_third = 1;
    int exception_fourth = 1;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
    ASSERT_EQUAL(res_fourth, exception_fourth);
}
CTEST(Utilites, Check_argv)
{
    // Given
    char* start_folder;
    char* dest_dir;
    char* arr[] = {"./documentary", "--version"};
    char* arr1[] = {"./documentary", "--help"};
    char* arr2[] = {"./documentary", "-inpdir", "./src", "-outdir", "./docs"};
    char* arr3[] = {"./documentary", "-outdir", "--help"};
    char* arr4[] = {"./documentary", "-outdir", "./docs"};
    // When
    int res_first = Check_argv(2, arr, &start_folder, &dest_dir);
    int res_second = Check_argv(2, arr1, &start_folder, &dest_dir);
    int res_third = Check_argv(5, arr2, &start_folder, &dest_dir);
    int res_fourth = Check_argv(3, arr3, &start_folder, &dest_dir);
    int res_fifth = Check_argv(3, arr4, &start_folder, &dest_dir);
    // Then
    int exception_first = 1;
    int exception_second = 1;
    int exception_third = 1;
    int exception_fourth = 0;
    int exception_fifth = 1;
    ASSERT_EQUAL(res_first, exception_first);
    ASSERT_EQUAL(res_second, exception_second);
    ASSERT_EQUAL(res_third, exception_third);
    ASSERT_EQUAL(res_fourth, exception_fourth);
    ASSERT_EQUAL(res_fifth, exception_fifth);
}

CTEST(Utilies, Get_file_extension)
{
    // Given
    char first[] = "./src/main.cpp";
    char second[] = "./src/bad.h";
    char third[] = "/main";
    // When
    char* res_first = Get_file_extension(first);
    char* res_second = Get_file_extension(second);
    char* res_third = Get_file_extension(third);
    // Then
    char* exception_first = "cpp";
    char* exception_second = "h";
    char* exception_third = "";
    ASSERT_STR(res_first, exception_first);
    ASSERT_STR(res_second, exception_second);
    ASSERT_STR(res_third, exception_third);
}