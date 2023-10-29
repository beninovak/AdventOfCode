#include <math.h>
#include <stdio.h>
#include <strings.h>

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 3\\input.txt", "r");

    char line[100];
    int length;
    int half;
    long total = 0;

    while(fgets(line, sizeof(line), fptr)) {
        if (line[0] == '\n') break;

        length = strlen(line);

        half = length / 2;

        char first[half + 1], second[half + 1]; // +1 for null termination...otherwise it's not a string

        for (int j = 0; j < half; j++) {
            first[j] = line[j];
            second[j] = line[j + half];
        }

        first[half] = second[half] = '\0'; // Make into string

        for (int k = 0; k < half; k++) {
            if (strchr(first, second[k]) != NULL) {
                printf("Contains same character: %c ", second[k]);

                if ((int)second[k] >= 65 && second[k] <= 90) {
                    total += ((int)second[k] - 38);
                } else if ((int)second[k] >= 97 && second[k] <= 122) {
                    total += ((int)second[k] - 96);
                }
                printf("Total: %ld\n", total);
                break;
            }
        }

    }

    return 0;
}
