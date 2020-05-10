#ifndef HANDLER_H
#define HANDLER_H
char* expansion_handle(char* str);
char** document_handle(char* paths);
int single_comment_check(char* str);
int multiline_comment_begin_check(char* str);
int multiline_comment_end_check(char* str);
int expan_check(char* filepath);
char* filename_without_expan(char* path);
char* no_html(char* str);
#endif