#include "macro.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/** Functions in this file makes checks on simple(non-documentary) comments.
 * These checks will be used for searching documentary comments and code lines*/

#define QTY_OF_EXTENSION 3
#define PROGRAM_VERSION "alpha1.0"

/// This function replaces < and > special characters for correct display in
/// html page
char* Escape_html(char* str)
{
    int len = (int)strlen(str);
    /// In the worst case, string is increased 3 times + '\0'
    char* without_html_str = (char*)calloc((len * 3) + 1, sizeof(char));
    int j = 0;
    for (int i = 0; i < len; i++, j++) {
        if (str[i] == '<') {
            without_html_str[j] = '&';
            without_html_str[j + 1] = 'l';
            without_html_str[j + 2] = 't';
            j += 2;
        } else if (str[i] == '>') {
            without_html_str[j] = '&';
            without_html_str[j + 1] = 'g';
            without_html_str[j + 2] = 't';
            j += 2;
        } else {
            without_html_str[j] = str[i];
        }
    }
    without_html_str[j] = '\0';
    free(str);
    return without_html_str;
}
/// This function returns file's name without its extension
const char* Get_filename_without_extension(char* path)
{
    char* temp_path = (char*)calloc(strlen(path), sizeof(char*));
    strcpy(temp_path, path);
    char* last_dot_ptr = strrchr(path, '.');
    if (last_dot_ptr == NULL) {
        return "";
    }
    int last_dot_index = last_dot_ptr - path;
    temp_path[last_dot_index] = '\0';
    temp_path = strrchr(temp_path, '/');
    return temp_path == NULL ? "" : temp_path + 1;
}
/// This function recursively finds paths to all files in folder
int Search_files_recursive(char* path, char** paths, int* recursive_exit_flag)
{
    DIR* d = opendir(path);
    if (d == NULL) {
        return 0;
    }
    struct dirent* dir;
    while ((dir = readdir(d)) != NULL) {
        /// Hidden and system files check
        if (dir->d_name[0] == '.') {
            continue;
        }
        if (*recursive_exit_flag == MAX_COUNT_OF_FILES) {
            return -1;
        }
        if (dir->d_type != DT_DIR) {
            char* f_path = (char*)calloc(MAX_PATH_LEN, sizeof(char));
            sprintf(f_path, "%s/%s", path, dir->d_name);
            strcpy(paths[*recursive_exit_flag], f_path);
            free(f_path);
            *recursive_exit_flag = *recursive_exit_flag + 1;
        } else if (
                dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0
                && strcmp(dir->d_name, "..") != 0) {
            char d_path[MAX_PATH_LEN * 2];
            sprintf(d_path, "%s/%s", path, dir->d_name);
            Search_files_recursive(d_path, paths, recursive_exit_flag);
        }
    }
    closedir(d);
    return 0;
}
/// This function returns array of data from file
char** Get_data_from_document(char* paths)
{
    FILE* myfile;
    myfile = fopen(paths, "r");
    if (myfile == NULL) {
        printf("%s%s%s\n", "On path ", paths, " file not found!");
        return 0;
    }
    char* ptrFile;
    int quan_str = 0;
    char** data = (char**)calloc(MAX_QTY_STR, sizeof(char*));
    for (int i = 0; i < MAX_QTY_STR; i++) {
        data[i] = (char*)calloc(MAX_LEN_INP_STR, sizeof(char));
    }
    while (quan_str < MAX_QTY_STR) {
        char* temp = (char*)calloc(MAX_LEN_INP_STR, sizeof(char));
        ptrFile = fgets(temp, MAX_LEN_INP_STR, myfile);
        if (ptrFile == NULL) {
            if (feof(myfile) != 0) {
                break;
            }
        }
        strcpy(data[quan_str], temp);
        quan_str++;
        free(temp);
    }
    fclose(myfile);
    return data;
}
/// This function returns file's extention
char* Get_file_extension(const char* path)
{
    char* last_dot_ptr = strrchr(path, '.');
    return last_dot_ptr == NULL ? "" : last_dot_ptr + 1;
}
void Print_help()
{
    printf("%s\n%s\n",
           "usage: documentary [--version] [--help]",
           "\t  [-inpdir <path>] [-outdir <path>]");
    printf("%s\n", "Available commands");
    printf("\t%s\n", "-inpdir");
    printf("\t%s\n", "-outdir");
    printf("\t%s\n", "--help");
    printf("\t%s\n", "--version");
}
int Check_argc(int argc)
{
    if (argc == 1) {
        printf("%s\n%s\n",
               "usage: documentary [--version] [--help]",
               "\t  [-inpdir <path>] [-outdir <path>]");
        return 0;
    }
    if (argc > 5 || argc == 4) {
        printf("\x1b[31m Error! \x1b[0m Invalid number of arguments");
        return 0;
    }
    return 1;
}
int Check_argv(int argc, char** array_argv, char** inpdir, char** outdir)
{
    const char input_directory[] = "-inpdir";
    const char output_directory[] = "-outdir";
    const char help_flag[] = "--help";
    const char version_flag[] = "--version";
    *inpdir = "";
    *outdir = "./";
    if (argc == 2) {
        if (strcmp(array_argv[1], help_flag) == 0) {
            Print_help();
            return 0;
        }
        if (strcmp(array_argv[1], version_flag) == 0) {
            printf("%s\n", PROGRAM_VERSION);
            return 0;
        }
    } else {
        for (int i = 1; i < argc; i++) {
            char* current_str = array_argv[i];
            char* next_str = array_argv[i + 1];
            int check_inp = strcmp(current_str, input_directory);
            int check_out = strcmp(current_str, output_directory);
            int check_help = strcmp(current_str, help_flag);
            int check_version = strcmp(current_str, version_flag);
            if (check_inp * check_out * check_help * check_version) {
                printf("\'%s\'%s \n",
                       array_argv[i],
                       " is not a command. See \'--help\'");
                return 0;
            }
            if (!check_inp) {
                if (!strcmp(next_str, help_flag)) {
                    printf("%s\n", "path to source dir");
                    return 0;
                } else {
                    if (array_argv[i + 1][0] != '.') {
                        printf("\'%s\'%s\n",
                               array_argv[i + 1],
                               " is wrong path");
                        return 0;
                    }
                    *inpdir = array_argv[i + 1];
                    i++;
                }
            }
            if (!check_out) {
                if (!strcmp(next_str, help_flag)) {
                    printf("%s\n", "path to output dir (default - )");
                    return 0;
                } else {
                    *outdir = array_argv[i + 1];
                    i++;
                }
            }
        }
    }
    return 1;
}
