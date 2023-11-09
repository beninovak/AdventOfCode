#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void moveTailIfNeeded(int* HX, int* HY, int* TX, int* TY, int** matrix) {

//    printf("HX: %p, HY: %p, TX: %p, TY: %p\n", HX, HY, TX, TY);
//    printf("*HX: %d, *HY: %d, *TX: %d, *TY: %d\n", *HX, *HY, *TX, *TY);
    fflush(stdout);

    if (*HX - 1 > *TX) {
        *TX = *TX + 1; // Note: this is not the same as *TX++;
        *TY = *HY;
        matrix[*TX][*TY] = 1;
    } else if (*HX + 1 < *TX) {
        *TX = *TX - 1;
        *TY = *HY;
        matrix[*TX][*TY] = 1;
    } else if (*HY - 1 > *TY) {
        *TY = *TY + 1;
        *TX = *HX;
        matrix[*TX][*TY] = 1;
    } else if (*HY + 1 < *TY) {
        *TY = *TY - 1;
        *TX = *HX;
        matrix[*TX][*TY] = 1;
    }
}

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 9\\input.txt", "r");
    int** matrix = calloc(1000, sizeof(int*) * 1000);

    for (int i = 0; i < 1000; i++) {
        matrix[i] = calloc(1000, sizeof(int*));
    }

    char line[10] = "";
    char* token;
    char command[2];
    int amountToMove;

    // Head and tail start at (500, 500) - the middle of the grid
    int hx = 500, hy = 500;
    int tx = 500, ty = 500;

    matrix[500][500] = 1;

//    int count = 0;

    while (fgets(line, sizeof(line), fptr)) {
//        count++;
//        if (count > 20) break;
        token = strtok(line, " ");
        strcpy(command, token);
        token = strtok(NULL, "\n");
        amountToMove = atoi(token);

        if (strcmp(command, "L") == 0) {
            for (int t = 0; t < amountToMove; t++) {
                hx--;
                moveTailIfNeeded(&hx, &hy, &tx, &ty, matrix);
            }
        } else if (strcmp(command, "R") == 0) {
            for (int t = 0; t < amountToMove; t++) {
                hx++;
                moveTailIfNeeded(&hx, &hy, &tx, &ty, matrix);
            }
        } else if (strcmp(command, "U") == 0) {
            for (int t = 0; t < amountToMove; t++) {
                hy--;
                moveTailIfNeeded(&hx, &hy, &tx, &ty, matrix);
            }
        } else if (strcmp(command, "D") == 0) {
            for (int t = 0; t < amountToMove; t++) {
                hy++;
                moveTailIfNeeded(&hx, &hy, &tx, &ty, matrix);
            }
        }
    }

    int uniquePositionsVisited = 0;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (matrix[i][j] == 1) {
                uniquePositionsVisited++;
            }
        }
    }

    printf("\nUnique positions visited: %d\n", uniquePositionsVisited);

    return 0;
}
