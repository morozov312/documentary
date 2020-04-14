#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3
char* expansion_handle(char str[])
{
    int max_len_expan=4;
    char* temp=(char*)malloc(max_len_expan*sizeof(char));
    int counter = 0;
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            counter++;
            unsigned long int j = 0;
            int k = i + 1;
            while (j <= strlen(temp)) {
                temp[j] = str[k];
                k++;
                j++;
            }
        }
    }
    if (counter == 1) {
        return temp;
    } else {
        return 0;
    }
}
int path_reading()
{
    FILE* myfile;
    myfile = fopen("./path/path.txt", "r");
    if (myfile == NULL) {
        printf("File path.txt not found!");
        return 0;
    }
    char *temp, *ptrFile;
    int max_len_inp_str=1000;
    int max_quan_str=100;
    int i=0;
    while (i<max_quan_str) {
        i++;
        temp = (char*)malloc(max_len_inp_str * sizeof(char));
        ptrFile = fgets(temp, max_len_inp_str, myfile);
        if (ptrFile == NULL) {
            if (feof(myfile) != 0) {
                break;
            } else {
                continue;
            }
        }
        temp=expansion_handle(temp);
        printf("%s\n", temp);
    }

    fclose(myfile);
    return 0;
}
