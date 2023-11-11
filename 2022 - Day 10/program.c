#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int iSCorrectCycle(int cycle) {
    if ((cycle == 20) || ((cycle - 20) % 40 == 0)) {
        return 1;
    }
    return 0;
}

int main() {

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    FILE *fptr;

    fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 10\\input.txt", "r");

    int X = 1;
    int amount;
    int strength;
    int totalStrength = 0;
    int cycle = 0;
    char line[10];
    char *token;

    // Read the content of file line by line
    while(fgets(line, 10, fptr)) {

        cycle++;

        if (iSCorrectCycle(cycle)) {
            strength = cycle * X;
            totalStrength += strength;
        }

        token = strtok(line, " ");
        if (strcmp(token, "addx") == 0) {
            cycle++;

            if (iSCorrectCycle(cycle)) {
                strength = cycle * X;
                totalStrength += strength;
            }

            token = strtok(NULL, " ");
            amount = atoi(token);
            X += amount;
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Sum of signal strengths: %d\n", totalStrength);
    printf("Time taken for execution: %f\n", cpu_time_used);

    fclose(fptr);
    return 0;
}