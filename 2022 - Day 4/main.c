#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 4\\input.txt", "r");

    char line[20];
    char *token, *token2, left[10], right[10], *elf1, *elf2;
    int elf1min, elf1max, elf2min, elf2max;
    int overlappingPairs = 0;

    while(fgets(line, sizeof(line), fptr)) {

        printf("Line: %s", line);

        token = strtok(line, ",\n");
        strcpy(left, token);
        token = strtok(NULL, ",\n");
        strcpy(right, token);

        elf1 = strtok(left, "-");
        elf1min = atoi(elf1);
        elf1 = strtok(NULL, "-");
        elf1max = atoi(elf1);

        elf2 = strtok(right, "-");
        elf2min = atoi(elf2);
        elf2 = strtok(NULL, "-");
        elf2max = atoi(elf2);

        if ((elf1min >= elf2min && elf1min <= elf2max) ||
            (elf1max >= elf2min && elf1max <= elf2max)) {
            overlappingPairs++;
            printf(" - Overlapping pairs so far: %d\n", overlappingPairs);
        } else if (
            (elf2min >= elf1min && elf2min <= elf1max) ||
            (elf2max >= elf1min && elf2max <= elf1max)) {
            overlappingPairs++;
        }
    }

    printf("Total number of overlapping pairs: %d", overlappingPairs);

    return 0;
}
