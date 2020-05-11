#ifndef HANDLER_H
#define HANDLER_H
char* get_file_extension(char* file_path);
char** get_data_from_document(char* paths);
int single_comment_check(char* str);
int multiline_comment_begin_check(char* str);
int multiline_comment_end_check(char* str);
int extension_check(char* filepath);
char* filename_without_extension(char* path);
char* exclude_html(char* str);
int check_document_multiline_commentary(char* string);
#endif