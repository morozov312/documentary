#include <stdio.h>
#include <stdlib.h>
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