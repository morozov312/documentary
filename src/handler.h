#ifndef HANDLER_H
#define HANDLER_H
char** path_reading(char path[], char** paths);
char* expansion_handle(char* str);
char** document_handle(char* paths);
int single_comment_check(char* str);
int multiline_comment_begin_check(char* str);
int multiline_comment_end_check(char* str);
int expan_check(char* filepath);
char* filename_without_expan(char* path);
int bracket_check(char* str);
int single_comment_code_check(char* str);
char* code_from_string_with_comment(char* str);
char* comment_from_string_with_code(char* str);
int comment_separator_check(char* str);
#endif