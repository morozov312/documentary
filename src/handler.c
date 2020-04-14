#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3
char* expansion_handle(char str[])
{
    int max_len=4;
    char* temp=(char*)malloc(max_len*sizeof(char));
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            counter++;
            int j = 0;
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
        printf("File open error!");
        return 0;
    }
    char *temp, *ptrFile;
    while (1) {
        temp = (char*)malloc(1000 * sizeof(char));
        ptrFile = fgets(temp, 1000, myfile);
        if (ptrFile == NULL) {
            if (feof(myfile) != 0) {
                break;
            } else {
                continue;
            }
        }
        printf("%s\n", temp);
    }

    fclose(myfile);
    return 0;
}
