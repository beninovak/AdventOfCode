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
    char ch;
    char num[5] = "";
    int numLength = 0;
    int counter;
    long partsSum = 0;
    int alreadyAdded;


    for (int j = 0; j < rows; j++) {
        for (int k = 0; k < columns; k++) {

            ch = matrix[j][k];
            if (isdigit(ch)) {

                alreadyAdded = 0;
                memset(num, 0, sizeof(num));

                counter = 0;
                while (isdigit(ch)) {
                    num[counter] = ch;
                    counter++;

                    ch = matrix[j][k + counter];
                }

                numLength = counter;

                // Check left from number
                if (k > 0 && isSymbol(matrix[j][k - 1]) == 1) {
                    partsSum += atoi(num);
                    alreadyAdded = 1;
                }

                // Check right from number
                if (alreadyAdded == 0 && k + numLength < columns && isSymbol(matrix[j][k + numLength]) == 1) {
                    partsSum += atoi(num);
                    alreadyAdded = 1;
                }

                // Check top row
                if (alreadyAdded == 0 && j > 0) {
                    for (int c = k - 1; c < k + numLength + 1; c++) {
                        if (c >= 0 && c < columns && isSymbol(matrix[j - 1][c]) == 1) {
                            partsSum += atoi(num);
                            alreadyAdded = 1;
                            break;
                        }
                    }
                }

                // Check bottom row
                if (alreadyAdded == 0 && j < rows - 1) {
                    for (int c = k - 1; c < k + numLength + 1; c++) {
                        if (c >= 0 && c < columns && isSymbol(matrix[j + 1][c]) == 1) {
                            partsSum += atoi(num);
                            break;
                        }
                    }
                }

                // counter - 1 because 'k' is incremented at the top of the loop anyway
                k += (counter - 1);
            }
        }
    }

    printf("Parts sum: %ld", partsSum);

    return 0;
}
