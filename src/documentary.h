#ifndef DOCUMENTARY_H
#define DOCUMENTARY_H
struct comment;
char* del_multiline_comment_begin(char* str);
char* del_multiline_comment_end(char* str);
char* del_multiline_comment_stars(char* str);
int html_generator(struct comment* list, char* path, int quan_structs);
char* file_name_generator(char* path);
void recursive_files_search(char* path, char** paths);
char* del_documentary_comment_symbols(char* string);
#endif