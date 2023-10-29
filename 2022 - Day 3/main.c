#include <math.h>
#include <stdio.h>
#include <strings.h>

int getPriority(char item) {
    if ((int)item >= 65 && item <= 90) {
        return ((int)item - 38);
    } else if ((int)item >= 97 && item <= 122) {
        return ((int)item - 96);
    }
    return 0;
}

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 3\\input.txt", "r");

    char line1[100], line2[100], line3[100];
    int lineSize = sizeof(line1);
    long total = 0;
    int count = 1;

    while(fgets(line1, lineSize, fptr)) {

        if (line1[0] == '\n') break;

        fgets(line2, lineSize, fptr);
        fgets(line3, lineSize, fptr);

        for (int i = 0; i < strlen(line1); i++) {

            if (strchr(line2, line1[i])) {
                if (strchr(line3, line1[i])) {
                    total += getPriority(line1[i]);
                    printf("Group %d badge: %c\n", count, line1[i]);
                    break;
                }
            }
        }

        count++;
    }

    printf("%ld", total);

    return 0;
}
