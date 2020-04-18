#ifndef DOCUMENTARY_H
#define DOCUMENTARY_H
struct comment {
    int type; // 0 - single comment , 1 - multiline comment
    char** comment_data;
    char* code_temp_string;
};
char* del_single_comment(char* str);
char* del_multiline_comment_begin(char str[]);
char* del_multiline_comment_end(char str[]);
char* del_multiline_comment_stars(char str[]);
int docs_gen(char** array, char* path);
void html_generator(struct comment array[], char* path, int quan_structs);
#endif