#ifndef PROCESSING_H
#define PROCESSING_H
typedef struct comment comment;
int Generate_html(comment* list, char* path, int qty_structs, char* dest_dir);
int Create_document(char* path, char* dest_dir);
int Check_code(char* str);
comment* Create_struct_of_data(int qty_lines, char** document_data);
#endif