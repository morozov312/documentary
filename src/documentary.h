#ifndef DOCUMENTARY_H
#define DOCUMENTARY_H
struct comment {
    char* comment_data;
    char* code_string;
};
char* del_multiline_comment_begin(char* str);
char* del_multiline_comment_end(char* str);
char* del_multiline_comment_stars(char* str);
int html_generator(struct comment* list, char* path, int quan_structs);
#endif