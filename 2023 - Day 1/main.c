#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isWordDigit(char word[50]) {

    if (strcmp(word, "zero") == 0 ||
        strcmp(word, "one") == 0 ||
        strcmp(word, "two") == 0 ||
        strcmp(word, "three") == 0 ||
        strcmp(word, "four") == 0 ||
        strcmp(word, "five") == 0 ||
        strcmp(word, "six") == 0 ||
        strcmp(word, "seven") == 0 ||
        strcmp(word, "eight") == 0 ||
        strcmp(word, "nine") == 0)
    {
        return 1;
    }

    return 0;
}

char wordToDigit(char word[50]) {
    if (strcmp(word, "zero") == 0) {
        return '0';
    } else if (strcmp(word, "one") == 0) {
        return '1';
    } else if (strcmp(word, "two") == 0) {
        return '2';
    } else if (strcmp(word, "three") == 0) {
        return '3';
    } else if (strcmp(word, "four") == 0) {
        return '4';
    } else if (strcmp(word, "five") == 0) {
        return '5';
    } else if (strcmp(word, "six") == 0) {
        return '6';
    } else if (strcmp(word, "seven") == 0) {
        return '7';
    } else if (strcmp(word, "eight") == 0) {
        return '8';
    } else if (strcmp(word, "nine") == 0) {
        return '9';
    }

    return 0;
}

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 1\\input.txt", "r");
    char line[100];
    int index;
    char digit;
    char num[3], firstDigit, lastDigit;
    int sum = 0;
    char word[50], substr[50];

    while (fgets(line, sizeof(line), fptr)) {

        index = 0;
        digit = ' ';
        firstDigit = lastDigit = '\0';
        memset(num, 0, sizeof(num));
        memset(word, 0, sizeof(word));

        while (line[index] != '\0') {

            digit = line[index];

            if (isdigit(digit)) {
                memset(word, 0, sizeof(word));

                if (firstDigit == '\0') {
                    firstDigit = digit;
                }
                lastDigit = digit;
            } else {
                for (int i = 0; i < sizeof(word); i++) {
                    if (word[i] == '\0') {
                        word[i] = digit;
                        break;
                    }
                }

                // No digit name in English is shorter than 3
                if (strlen(word) >= 3) {

                    for (int i = 0; i < strlen(word); i++) {
                        memset(substr, 0, sizeof(substr));

                        for (int j = strlen(word) - 1; j >= 0; j--) {
                            for (int k = i; k <= j; k++) {
                                if (word[k] == '\0') break;
                                substr[k - i] = word[k];
                            }

                            if (isWordDigit(substr) == 1) {
                                if (firstDigit == '\0') {
                                    firstDigit = wordToDigit(substr);
                                }

                                lastDigit = wordToDigit(substr);
                                break;
                            }
                        }
                    }
                }
            }

            index ++;
        }

        num[0] = firstDigit;
        num[1] = lastDigit;
        sum += atoi(num);
        printf("%c %c -> %d = %d\n", firstDigit, lastDigit, atoi(num), sum);
    }

    printf("Sum: %d", sum);

    return 0;
}
