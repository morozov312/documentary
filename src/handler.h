#ifndef HANDLER_H
#define HANDLER_H
char** path_reading(char path[], char** paths);
char* expansion_handle(char str[]);
char** document_handle(char* paths);
int single_comment_check(char str[]);
int muitiline_comment_begin_check(char str[]);
int muitiline_comment_end_check(char str[]);
int expan_check(char filepath[]);
#endif