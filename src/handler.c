#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3

char* expansion_handle(char str[])
{
    char temp[4];
    int counter = 0;
    for (int i = 0; str[i] != "\0"; i++) {
        if (str[i] == ".") {
            counter++;
            int j = 0;
            int k = i + 1;
            while (j <= 4) {
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
