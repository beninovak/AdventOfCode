#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void insertionSort(long array[], int arrayCount) {

    printf("%d", arrayCount);

    int i, key, j;

    for (i = 1; i < arrayCount; i++) {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

int main() {

    FILE *fptr;

    fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 1\\input.txt", "r");

    char line[10];
    long elves[2000];
    int elf = 0;
    int amount = 0;

    // Read the content of file line by line
    while (fgets(line, sizeof line, fptr)) {

        if (line[0] == '\n') {
            printf("New line\n");
            elves[elf] = amount;
            amount = 0;
            elf++;
            continue;
        } else if (strcmp(line, "--") == 0) {
            printf("New -- line\n");
            elves[elf] = amount;
            break;
        }

        printf("%ld\n", atoi(line));
        amount += atoi(line);
    }

    long maxCalories = 0;

    for (int i = 0; i <= elf; i++) {

        if (elves[i] == 0) break;

        if (elves[i] > maxCalories) {
            maxCalories = elves[i];
        }

        printf("Elf %d - %ld\n", (i + 1), elves[i]);
    }

    insertionSort(elves, elf + 1); // Elf is the last index of array...function needs length
    long topThree = elves[elf] + elves[elf - 1] + elves[elf - 2];

    printf("The top three elves with the most calories are carrying %ld calories.", topThree);
}