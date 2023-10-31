#include <stdio.h>

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 6\\input.txt", "r");
    char letter, lastFour[5] = "\0\0\0\0\0";
    int counter = 1;
    int containsDuplicate;

    while ((letter = getc(fptr)) != EOF) {

        containsDuplicate = 0;
        lastFour[0] = lastFour[1];
        lastFour[1] = lastFour[2];
        lastFour[2] = lastFour[3];
        lastFour[3] = letter;

        for (int i = 0; i < 3; i++) {
            for (int j = 3; j > i; j--) {
                if (lastFour[i] == lastFour[j]) {
                    containsDuplicate = 1;
                    break;
                }
            }
            if (containsDuplicate == 1) break;
        }

        if (counter >= 4 && containsDuplicate == 0) {
            printf("First marker is complete after: %d characters.\n", counter);
            printf("The marker is: %s", lastFour);
            break;
        }

        counter++;
    }

    return 0;
}
