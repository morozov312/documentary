#ifndef HANDLER_H
#define HANDLER_H
char* get_file_extension(char* file_path);
char** document_handle(char* paths);
int single_comment_check(char* str);
int multiline_comment_begin_check(char* str);
int multiline_comment_end_check(char* str);
int extention_check(char* filepath);
char* filename_without_extension(char* path);
char* no_html(char* str);
#endif