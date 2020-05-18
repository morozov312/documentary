#include "advanced_check.h"
#include "advanced_handle.h"
#include "comments_check.h"
#include "comments_delete.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_INP_STR 500
#define MAX_QTY_STR 50 * 1000

int qty_structs = 0;

typedef struct {
    char* comment_data;
    char* code_string;
} comment;

int html_generator(comment* list, char* path, int qty_structs)
{
    FILE *documentary, *styles;
    char* ptrFile;
    char* name = file_name_generator(path);
    documentary = fopen(name, "w");
    if (documentary == NULL) {
        printf("%s\n", "Error create html page!");
        return 0;
    }
    /// Header
    styles = fopen("./styles/styles.html", "r");
    if (styles == NULL) {
        printf("%s\n", "Error, stylesheet not found!");
        return 0;
    }
    while (1) {
        char* temp = (char*)calloc(MAX_LEN_INP_STR, sizeof(char));
        ptrFile = fgets(temp, MAX_LEN_INP_STR, styles);
        if (ptrFile == NULL) {
            if (feof(styles) != 0) {
                break;
            } else {
                continue;
            }
        }
        fputs(temp, documentary);
        free(temp);
    }
    fclose(styles);
    char* filename = filename_without_extension(path);
    fputs(filename, documentary);
    fputs("</h2>", documentary);
    /// document programming language definition
    fputs(get_document_type(path), documentary);
    // main content
    for (int i = 0; i < qty_structs; i++) {
        if (list[i].comment_data) {
            fputs("<p class=\"comment\">", documentary);
            fputs(list[i].comment_data, documentary);
            fputs("</br></p>", documentary);
            if (strlen(list[i].code_string)) {
                fputs("<code>", documentary);
                fputs(list[i].code_string, documentary);
                fputs("</code></br></br>", documentary);
            }
        }
    }
    /// Footer
    fputs("</div></body></html>", documentary);
    fclose(documentary);
    free(name);
    return 1;
}
int check_code(char* str)
{
    int single_flag = check_single_comment(str);
    int multiline_begin_flag = check_multiline_comment_begin(str);
    int multiline_end_flag = check_multiline_comment_end(str);
    if (!single_flag && !multiline_begin_flag && !multiline_end_flag) {
        return 1;
    }
    return 0;
}
comment* create(int count, char** doc)
{
    comment* comments_array = (comment*)calloc(count, sizeof(comment));
    int start_flag = 0;
    qty_structs = 0;
    for (int i = 0; i < count - 1; i++) {
        char* current_str = doc[i];
        char* next_str = doc[i + 1];
        char* str_whithout_star = del_multiline_comment_stars(current_str);
        char* str_whithout_document_comment_symb
                = del_documentary_comment_symbols(current_str);
        int multiline_begin_flag = check_multiline_comment_begin(current_str);
        int multiline_end_flag = check_multiline_comment_end(current_str);
        int multiline_document_flag
                = check_multiline_documentary_comment(current_str);
        int singleline_document_flag
                = check_single_documentary_comment(current_str);
        int code_check_flag = check_code(next_str);
        if (multiline_document_flag && !start_flag) {
            start_flag = 1;
            comments_array[qty_structs].comment_data
                    = str_whithout_document_comment_symb;
            comments_array[qty_structs].code_string = "";
            if (!multiline_end_flag) {
                qty_structs++;
            }
        } else if (start_flag && !multiline_end_flag && !multiline_begin_flag) {
            comments_array[qty_structs].comment_data = str_whithout_star;
            comments_array[qty_structs].code_string = "";
            qty_structs++;
        } else if (multiline_end_flag) {
            comments_array[qty_structs].comment_data
                    = del_multiline_comment_end(str_whithout_star);
            if (code_check_flag) {
                comments_array[qty_structs].code_string = next_str;
            } else {
                comments_array[qty_structs].code_string = "";
            }
            qty_structs++;
            start_flag = 0;
        } else if (singleline_document_flag && !start_flag) {
            comments_array[qty_structs].comment_data
                    = str_whithout_document_comment_symb;
            if (code_check_flag) {
                comments_array[qty_structs].code_string = next_str;
            } else {
                comments_array[qty_structs].code_string = "";
            }
            qty_structs++;
        }
    }
    return comments_array;
};
int document_creation(char* path)
{
    int valid_check = check_extension(path);
    if (!valid_check) {
        printf("%s%s\n", "Unsupported file format on - ", path);
        return 0;
    }
    char** document_data = get_data_from_document(path);
    int count_of_lines = 0;
    if (document_data == NULL) {
        return 0;
    }
    for (int i = 0; i < MAX_QTY_STR; i++) {
        if (strlen(document_data[i]) != 0) {
            document_data[i] = exclude_html(document_data[i]);
            count_of_lines++;
        }
    }
    /// this error appears if the document empty ot has 1 line
    if (count_of_lines <= 1) {
        printf("%s%s", "Error,file on path ", path);
        printf("%s\n", " too small for documentation");
        return 0;
    }
    comment* comments_array = create(count_of_lines, document_data);
    if (qty_structs == 0) {
        printf("%s%s%s\n",
               "In file - ",
               path,
               " no documentary comments found");
        return 0;
    }
    int creation_flag = html_generator(comments_array, path, qty_structs);
    if (creation_flag) {
        printf("%s%s\n", "Successfully created documentation on file - ", path);
    }
    for (int i = 0; i < MAX_QTY_STR; i++) {
        free(document_data[i]);
    }
    free(document_data);
    free(comments_array);
    return 0;
}