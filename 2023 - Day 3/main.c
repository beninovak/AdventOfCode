#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int isSymbol(char c) {
    return !isdigit(c) && c != '.';
}

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 3\\input.txt", "r");
    char line[200] = "";
    char** matrix;

    // Get row count
    int rows = 0;
    while (fgets(line, sizeof(line), fptr)) {
        rows++;
    }
    rewind(fptr);

    // Get column count
    int columns = 0;
    while(getc(fptr) != '\n') {
        columns++;
    }
    rewind(fptr);

    // Setup matrix
    matrix = calloc(rows, sizeof(char) * columns);
    int count = 0;
    while (fgets(line, sizeof(line), fptr)) {
        matrix[count] = calloc(columns, 1);

        for (int i = 0; i < columns; i++) {
            matrix[count][i] = line[i];
        }

        count++;
    }

    fclose(fptr);

    // Traverse matrix
    char num[5] = "";
    int numLength;
    int counter;
    int numbersCount;
    char digit;
    int index, num1, num2;
    long long gearsSum = 0;

    for (int j = 0; j < rows; j++) {
        for (int k = 0; k < columns; k++) {
            if (matrix[j][k] == '*') {

                num1 = num2 = numbersCount = 0;

                // Check left from number
                if (k > 0 && isdigit(matrix[j][k - 1]) == 1) {

                    memset(num, 0, sizeof(num));

                    index = k - 1;
                    counter = numLength = 0;

                    digit = matrix[j][index];
                    while (isdigit(digit) && index >= 0) {
                        numLength++;
                        index--;
                        digit = matrix[j][index];
                    }

                    index = k - numLength;
                    digit = matrix[j][index];
                    while (isdigit(digit)) {
                        num[counter] = digit;
                        index++;
                        digit = matrix[j][index];
                        counter++;
                    }

                    num1 = atoi(num);
                    numbersCount++;
                }

                // Check right from number
                if (k < columns && isdigit(matrix[j][k + 1]) == 1) {

                    memset(num, 0, sizeof(num));

                    index = k + 1;
                    counter = 0;

                    digit = matrix[j][index];
                    while (isdigit(digit)) {
                        num[counter] = digit;
                        index++;
                        digit = matrix[j][index];
                        counter++;
                    }

                    if (num1 == 0) {
                        num1 = atoi(num);
                    } else {
                        num2 = atoi(num);
                    }

                    numbersCount++;
                }

                // Check top row
                if (j > 0) {

                    int i;
                    if (k > 0) {
                         i = k - 1;
                    } else {
                        i = 0;
                    }

                    for (i; i <= k + 1; i++) {
                        if (isdigit(matrix[j - 1][i])) {

                            memset(num, 0, sizeof(num));

                            counter = numLength = 0;

                            index = i;
                            int forwards = 0;
                            while (1) {

                                if (!forwards) {
                                    index--;
                                    numLength++;

                                    digit = matrix[j - 1][index];

                                    if (!isdigit(digit)) {
                                        index++;
                                        forwards = 1;
                                    }

                                } else {
                                    digit = matrix[j - 1][index];
                                    index++;

                                    if (!isdigit(digit)) {
                                        break;
                                    }

                                    num[counter] = digit;
                                    counter++;
                                }
                            }

                            i++;

                            if (isdigit(matrix[j - 1][k])) {
                                i++;
                            }

                            if (num1 == 0) {
                                num1 = atoi(num);
                            } else {
                                num2 = atoi(num);
                            }

                            numbersCount++;
                        }
                    }
                }

                if (numbersCount > 2) continue;

                // Check bottom row
                if (j < rows - 1) {

                    int i;
                    if (k > 0) {
                         i = k - 1;
                    } else {
                        i = 0;
                    }

                    for (i; i <= k + 1; i++) {
                        if (isdigit(matrix[j + 1][i])) {

                            memset(num, 0, sizeof(num));

                            counter = numLength = 0;

                            index = i;
                            int forwards = 0;
                            while (1) {

                                if (!forwards) {
                                    index--;
                                    numLength++;

                                    digit = matrix[j + 1][index];

                                    if (!isdigit(digit)) {
                                        index++;
                                        forwards = 1;
                                    }

                                } else {
                                    digit = matrix[j + 1][index];
                                    index++;

                                    if (!isdigit(digit)) {
                                        break;
                                    }

                                    num[counter] = digit;
                                    counter++;
                                }
                            }

                            i++;

                            if (isdigit(matrix[j + 1][k])) {
                                i++;
                            }

                            if (num1 == 0) {
                                num1 = atoi(num);
                            } else {
                                num2 = atoi(num);
                            }

                            numbersCount++;
                        }
                    }
                }

                if (numbersCount != 2) continue;

//                printf("\nRow: %d Column: %d", j + 1, k + 1);
//                printf("\nNum 1: %d, num 2: %d", num1, num2);
//                printf("\nGear ratio %d", num1 * num2);
//                printf("\n--------------------------------------");

                gearsSum += (num1 * num2);
            }
        }
    }

    printf("\nGears sum: %lld ", gearsSum);

    return 0;
}
