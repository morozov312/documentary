#ifndef PROCESSING_H
#define PROCESSING_H
struct comment;
int html_generator(struct comment* list, char* path, int quan_structs);
int document_creation(char* path);
int code_check(char* str);
struct comment* create(int count, char** doc);
#endif