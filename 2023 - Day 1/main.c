#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 1\\input.txt", "r");
    char line[50];
    int index;
    char byte;
    char num[3] = "", lastByte;
    int sum = 0;

    while (fgets(line, sizeof(line), fptr)) {

        index = 0;
        byte = ' ';
        strcpy(num, "");

        while (line[index] != '\0') {
            byte = line[index];

            if (isdigit(byte)) {
                if (strcmp(num, "") == 0) {
                    num[0] = byte;
                }

                lastByte = byte;
            }

            index ++;
        }

        num[1] = lastByte;
        sum += atoi(num);
        printf("\n");
    }

    printf("Sum: %d", sum);

    return 0;
}
