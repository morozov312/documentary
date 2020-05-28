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

/** if founded begin of multiline documentary comment -> start flag == true */
int qty_structs = 0, start_flag = 0;

typedef struct {
    char* comment_data;
    char* code_string;
} comment;

int Generate_html(comment* list, char* path, int qty_structs, char* dest_dir)
{
    FILE *documentary, *styles;
    char* ptrFile;
    char* name = Generate_filename(path, dest_dir);
    documentary = fopen(name, "w");
    if (documentary == NULL) {
        printf("%s\n", "Error Create_struct_of_data html page!");
        return 0;
    }
    /// header
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
    char* filename = Get_filename_without_extension(path);
    fputs(filename, documentary);
    fputs("</h2>", documentary);
    /// document programming language definition
    fputs(Get_document_type(path), documentary);
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
    /// footer
    fputs("</div></body></html>", documentary);
    fclose(documentary);
    free(name);
    return 1;
}
int Check_code(char* str)
{
    int single_flag = Check_single_comment(str);
    int multiline_begin_flag = Check_multiline_comment_begin(str);
    int multiline_end_flag = Check_multiline_comment_end(str);
    if (!single_flag && !multiline_begin_flag && !multiline_end_flag) {
        return 1;
    }
    return 0;
}
comment* Create_struct_of_data(int qty_lines, char** document_data)
{
    comment* comments_array = (comment*)calloc(qty_lines, sizeof(comment));
    qty_structs = 0;
    for (int i = 0; i < qty_lines - 1; i++) {
        //=========================================================================
        char* current_s = document_data[i];
        char* next_s = document_data[i + 1];
        int multiline_begin_flag = Check_multiline_comment_begin(current_s);
        int multiline_end_flag = Check_multiline_comment_end(current_s);
        int multiline_doc_flag = Check_multiline_documentary_comment(current_s);
        int singleline_doc_flag = Check_single_documentary_comment(current_s);
        int code_Check_flag = Check_code(next_s);
        char* str_whithout_star = Del_multiline_comment_stars(current_s);
        char* str_whithout_doc = Del_documentary_comment_symbols(current_s);
        char* s_whithout_end = Del_multiline_comment_end(str_whithout_star);
        //========================================================================
        /// Check to begin multiline documentary comment
        if (multiline_doc_flag && !start_flag) {
            start_flag = 1;
            comments_array[qty_structs].comment_data = str_whithout_doc;
            comments_array[qty_structs].code_string = "";
            if (!multiline_end_flag) {
                qty_structs++;
            }
        }
        /// search lines between end and begin multiline doucumentary comment
        if (start_flag && !multiline_end_flag && !multiline_begin_flag) {
            comments_array[qty_structs].comment_data = str_whithout_star;
            comments_array[qty_structs].code_string = "";
            qty_structs++;
        }
        /// Checking at the end of the documentary comment
        if (multiline_end_flag) {
            /// in case if multiline comment writing in one-line
            if (multiline_begin_flag) {
                char* no_symb = Del_documentary_comment_symbols(s_whithout_end);
                comments_array[qty_structs].comment_data = no_symb;
            } else {
                comments_array[qty_structs].comment_data = s_whithout_end;
            }
            //=============================================================
            if (code_Check_flag) {
                comments_array[qty_structs].code_string = next_s;
            } else {
                comments_array[qty_structs].code_string = "";
            }
            qty_structs++;
            start_flag = 0;
        }
        /// search singleline comment if there wasn't start of multiline comment
        if (singleline_doc_flag && !start_flag) {
            comments_array[qty_structs].comment_data = str_whithout_doc;
            if (code_Check_flag) {
                comments_array[qty_structs].code_string = next_s;
            } else {
                comments_array[qty_structs].code_string = "";
            }
            qty_structs++;
        }
    }
    return comments_array;
}
int Create_document(char* path, char* dest_dir)
{
    start_flag = 0;
    int valid_Check = Check_extension(path);
    if (!valid_Check) {
        printf("%s%s\n", "Unsupported file format on - ", path);
        return 0;
    }
    char** document_data = Get_data_from_document(path);
    int count_of_lines = 0;
    /// if file cannot be read
    if (document_data == NULL) {
        return 0;
    }
    for (int i = 0; i < MAX_QTY_STR; i++) {
        if (strlen(document_data[i]) != 0) {
            document_data[i] = Escape_html(document_data[i]);
            count_of_lines++;
        }
    }
    /// this error appears if the document empty ot has 1 line
    if (count_of_lines <= 1) {
        printf("%s%s", "Error,file on path ", path);
        printf("%s\n", " too small for documentation");
        return 0;
    }
    /// calling function of the main algorithm
    comment* comments_array
            = Create_struct_of_data(count_of_lines, document_data);
    /// if was a beginning of a documentary comment but there wasn't end
    if (start_flag) {
        printf("%s%s\n", "Syntax error in file - ", path);
        return 0;
    }
    if (qty_structs == 0) {
        printf("%s%s%s\n",
               "In file - ",
               path,
               " there are no documentary comments");
        return 0;
    }
    int creation_flag
            = Generate_html(comments_array, path, qty_structs, dest_dir);
    if (creation_flag) {
        printf("%s%s\n",
               "\x1b[32mSuccessfully Create_struct_of_datad documentation on "
               "file -\x1b[0m",
               path);
    }
    //======================================
    for (int i = 0; i < MAX_QTY_STR; i++) {
        free(document_data[i]);
    }
    free(document_data);
    free(comments_array);
    //=======================================
    return 0;
}
