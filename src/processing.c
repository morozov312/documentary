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
    int single = check_single_comment(str);
    int m_b = check_multiline_comment_begin(str);
    int m_e = check_multiline_comment_end(str);
    if (!single && !m_b && !m_e) {
        return 1;
    }
    return 0;
}
comment* create(int count, char** doc)
{
    comment* comments_array = (comment*)calloc(count, sizeof(comment));
    int qty = 0, begin = 0;
    for (int i = 0; i < count - 1; i++) {
        char* current_str = doc[i];
        char* next_str = doc[i + 1];
        int m_b = check_multiline_comment_begin(current_str);
        int m_e = check_multiline_comment_end(current_str);
        if (check_multiline_documentary_comment(current_str) && !begin) {
            begin = 1;
            comments_array[qty].comment_data
                    = del_documentary_comment_symbols(current_str);
            comments_array[qty].code_string = "";
            if (!m_e) {
                qty++;
            }
        }
        if (begin && !m_e && !m_b) {
            comments_array[qty].comment_data
                    = del_multiline_comment_stars(current_str);
            comments_array[qty].code_string = "";
            qty++;
        }
        if (check_single_documentary_comment(current_str) && !begin) {
            comments_array[qty].comment_data
                    = del_documentary_comment_symbols(current_str);
            if (check_code(next_str)) {
                comments_array[qty].code_string = next_str;
            } else {
                comments_array[qty].code_string = "";
            }
            qty++;
        }
        if (m_e) {
            comments_array[qty].comment_data
                    = del_multiline_comment_end(current_str);
            if (check_code(next_str)) {
                comments_array[qty].code_string = next_str;
            } else {
                comments_array[qty].code_string = "";
            }
            qty++;
            begin = 0;
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
    int count_of_lines = 0, qty_structs = 0;
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
    for (int i = 0; i < count_of_lines; i++) {
        if (comments_array[i].comment_data != NULL) {
            qty_structs++;
        }
    }
    if (qty_structs == 0) {
        printf("%s%s%s\n",
               "In file - ",
               path,
               " no documentary comments found");
        return 0;
    }
    int res = html_generator(comments_array, path, qty_structs);
    if (res) {
        printf("%s%s\n", "Successfully created documentation on file - ", path);
    }
    for (int i = 0; i < MAX_QTY_STR; i++) {
        free(document_data[i]);
    }
    free(document_data);
    free(comments_array);
    return 0;
}