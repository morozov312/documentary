#ifndef UTILITIES_H
#define UTILITIES_H
char* Escape_html(char* str);
char* Get_filename_without_extension(char* path);
int Search_files_recursive(char* path, char** paths, int* recursive_exit_flag);
char** Get_data_from_document(char* paths);
char* Get_file_extension(const char* path);
int Check_argc(int argc,char** array_argv);
int Check_argv(int argc, char** array_argv, char** inpdir, char** outdir);
void Print_help();
#endif