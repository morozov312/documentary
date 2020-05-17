#ifndef UTILITIES_H
#define UTILITIES_H
char* exclude_html(char* str);
char* filename_without_extension(char* path);
void recursive_files_search(char* path, char** paths);
char* get_inpdir(int qty, char* array_argv[]);
char* get_outdir(int qty, char* array_argv[]);
char** get_data_from_document(char* paths);
char* get_file_extension(const char* path);
#endif