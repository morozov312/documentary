#ifndef DOCUMENTARY_H
#define DOCUMENTARY_H
struct comment {
    int type; // 0 - single comment , 1 - multiline comment
    char** comment_data;
    char* code_string;
};
char* del_single_comment(char* str);
char* del_multiline_comment_begin(char* str);
char* del_multiline_comment_end(char* str);
char* del_multiline_comment_stars(char* str);
int docs_gen(char** document_data, char* path);
int html_generator(struct comment* list, char* path, int quan_structs);
#endif