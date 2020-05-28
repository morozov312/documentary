#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Functions in this file makes checks on simple(non-documentary) comments.
 * These checks will be used for searching documentary comments and code lines*/

#define MAX_LEN_INP_STR 500
#define MAX_QTY_STR 50 * 1000
#define QTY_OF_EXTENSION 3
#define MAX_PATH_LEN 255
#define MAX_COUNT_OF_FILES 30

/// Count of read paths
int counter = 0;
int recursive_exit_flag = 0;

/// This function replaces < and > special characters for correct display in
/// html page
char* exclude_html(char* str)
{
    size_t len = (int)strlen(str);
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
const char* filename_without_extension(char* path)
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
void recursive_files_search(char* path, char** paths)
{
    DIR* d = opendir(path);
    if (d == NULL)
        return;
    struct dirent* dir;
    while ((dir = readdir(d)) != NULL) {
        /// Hidden and system files check
        if (dir->d_name[0] == '.') {
            continue;
        }
        if (recursive_exit_flag == 1) {
            return;
        }
        if (counter == MAX_COUNT_OF_FILES) {
            printf("%s\n",
                   "\x1b[36m Warning!\x1b[0m, limit of files for this "
                   "folder "
                   "overpassed!");
            recursive_exit_flag = 1;
            return;
        }
        if (dir->d_type != DT_DIR) {
            char* f_path = (char*)calloc(MAX_PATH_LEN, sizeof(char));
            sprintf(f_path, "%s/%s", path, dir->d_name);
            strcpy(paths[counter], f_path);
            free(f_path);
            counter++;
        } else if (
                dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0
                && strcmp(dir->d_name, "..") != 0) {
            char d_path[MAX_PATH_LEN * 2];
            sprintf(d_path, "%s/%s", path, dir->d_name);
            recursive_files_search(d_path, paths);
        }
    }
    closedir(d);
}
/// This function returns input directory from command line arguments
char* get_inpdir(int qty, char* array_argv[])
{
    const char input_directory[] = "-inpdir";
    const char output_directory[] = "-outdir";
    for (int i = 1; i < qty; i++) {
        if (strcmp(array_argv[i], input_directory) != 0
            && strcmp(array_argv[i], output_directory) != 0) {
            printf("%s%s\n", "Unknown option: ", array_argv[i]);
            continue;
        }
        if (strcmp(array_argv[i], output_directory) == 0) {
            i++;
            continue;
        }
        if (strcmp(array_argv[i], input_directory) == 0) {
            return array_argv[i + 1];
        }
    }
    return "";
}
/// This function returns output directory from command line arguments
char* get_outdir(int qty, char* array_argv[])
{
    const char input_directory[] = "-inpdir";
    const char output_directory[] = "-outdir";
    for (int i = 1; i < qty; i++) {
        if (strcmp(array_argv[i], input_directory) != 0
            && strcmp(array_argv[i], output_directory) != 0) {
            printf("%s%s\n", "Unknown option: ", array_argv[i]);
            continue;
        }
        if (strcmp(array_argv[i], input_directory) == 0) {
            i++;
            continue;
        }
        if (strcmp(array_argv[i], output_directory) == 0) {
            return array_argv[i + 1];
        }
    }
    return "./docs";
}
/// This function returns array of data from file
char** get_data_from_document(char* paths)
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
char* get_file_extension(const char* path)
{
    char* last_dot_ptr = strrchr(path, '.');
    return last_dot_ptr == NULL ? "" : last_dot_ptr + 1;
}
