#ifndef UTILITIES_H
#define UTILITIES_H
char* Escape_html(char* str);
char* Get_filename_without_extension(char* path);
void Search_files_recursive(char* path, char** paths);
char* Get_inpdir(int qty, char* array_argv[]);
char* Get_outdir(int qty, char* array_argv[]);
char** Get_data_from_document(char* paths);
char* Get_file_extension(const char* path);
#endif