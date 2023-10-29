#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int addToTotal(int cycle);

int main() {

    FILE *fptr;

    fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 10\\input.txt", "r");

    int X = 1;
    int amount = 0;
    int strength = 0;
    int totalStrength = 0;
    int cycle = 0;
    char line[10];

    // Read the content of file line by line
    while(fgets(line, 10, fptr)) {

        bool isNoop = (strcmp(line, "noop") == 1);

        if (isNoop) {
            cycle++;
            strength = cycle * X;
        } else {

            cycle++;
            strength = cycle * X;

            if (addToTotal(cycle) == 1)  {
                totalStrength += strength;
            }

            cycle++;
            strength = cycle * X;

            char *token = strtok(line, " ");
            while (token != NULL) {

                token = strtok(NULL, " ");
                amount = atoi(token);

                if (amount != 0) {
                    X += amount;
                }
            }
        }

        if (addToTotal(cycle) == 1)  {
            totalStrength += strength;
        }
    }

    printf("Sum of signal strengths: %d", totalStrength);

    fclose(fptr);
    return 0;
}

int addToTotal(int cycle) {

    if ((cycle == 20) || ((cycle - 20) % 40 == 0)) {
        return 1;
    }

    return 0;
}