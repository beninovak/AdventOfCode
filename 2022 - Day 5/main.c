#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  [V]     [B]                     [F]
//  [N] [Q] [W]                 [R] [B]
//  [F] [D] [S]     [B]         [L] [P]
//  [S] [J] [C]     [F] [C]     [D] [G]
//  [M] [M] [H] [L] [P] [N]     [P] [V]
//  [P] [L] [D] [C] [T] [Q] [R] [S] [J]
//  [H] [R] [Q] [S] [V] [R] [V] [Z] [S]
//  [J] [S] [N] [R] [M] [T] [G] [C] [D]
//   1   2   3   4   5   6   7   8   9

void arrayShiftLeft(char array[], int arrayLength, int shiftSpaces) {
    for (int i = 0; i < arrayLength; i++) {
        array[i] = array[i + shiftSpaces];
    }
}

void arrayShiftRight(char array[], int arrayLength, int shiftSpaces) {
    for (int j = arrayLength - 1; j > 0; j--) {
        array[j] = array[j - shiftSpaces];
    }
}

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 5\\input.txt", "r");
    char line[30], lastCommand[5], finalString[10] = "";
    char *token;
    int moveQuantity, stackToMoveFrom, stackToMoveTo;
    const int matrixRows = 9;
    const int matrixRowSize = 50;
    char matrix[9][50] = {
        { 'V', 'N', 'F', 'S', 'M', 'P', 'H', 'J' },
        { 'Q', 'D', 'J', 'M', 'L', 'R', 'S' },
        { 'B', 'W', 'S', 'C', 'H', 'D', 'Q', 'N' },
        { 'L', 'C', 'S', 'R' },
        { 'B', 'F', 'P', 'T', 'V', 'M' },
        { 'C', 'N', 'Q', 'R', 'T' },
        { 'R', 'V', 'G' },
        { 'R', 'L', 'D', 'P', 'S', 'Z', 'C' },
        { 'F', 'B', 'P', 'G', 'V', 'J', 'S', 'D' },
    };

    while (fgets(line, sizeof(line), fptr)) {

        token = strtok(line, " "); // Get rid of "move" command
        token = strtok(NULL, " "); // Get first number
        moveQuantity = atoi(token);

        while(token != NULL) {

            token = strtok(NULL, " \n");
            if (token == NULL) break;

            if (strcmp(token, "from") == 0 || strcmp(token, "to") == 0) {
                strcpy(lastCommand, token);
            } else {
                if (strcmp(lastCommand, "from") == 0) {
                    stackToMoveFrom = atoi(token) - 1;
                } else if (strcmp(lastCommand, "to") == 0) {
                    stackToMoveTo = atoi(token) - 1;
                }
            }
        }

        arrayShiftRight(matrix[stackToMoveTo], matrixRowSize, moveQuantity);
        for (int i = 0; i < moveQuantity; i++) {
            matrix[stackToMoveTo][i] = matrix[stackToMoveFrom][i];
        }
        arrayShiftLeft(matrix[stackToMoveFrom], matrixRowSize, moveQuantity);

    }

    for (int i = 0; i < matrixRows; i++) {
        finalString[i] = matrix[i][0];
    }

    printf("Top crates are: %s", finalString);

    // Part 1 result: SBPQRSCDF
    // Part 2 result: RGLVRCQSB

    return 0;
}
