#ifndef PROCESSING_H
#define PROCESSING_H
typedef struct comment comment;
int html_generator(comment* list, char* path, int quan_structs, char* dest_dir);
int document_creation(char* path, char* dest_dir);
int check_code(char* str);
comment* create(int count, char** doc);
#endif