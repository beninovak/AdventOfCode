#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void moveTailIfNeeded(int nodeToCheck, int** nodes) {

//    printf("HX: %p, HY: %p, TX: %p, TY: %p\n", HX, HY, TX, TY);
//    printf("*HX: %d, *HY: %d, *TX: %d, *TY: %d\n", *HX, *HY, *TX, *TY);
//    fflush(stdout);

    int* HX = &nodes[nodeToCheck - 1][0];
    int* HY = &nodes[nodeToCheck - 1][1];
    int* TX = &nodes[nodeToCheck][0];
    int* TY = &nodes[nodeToCheck][1];

    if ((*HX - *TX == 2 || *HX - *TX == -2) && (*HY - *TY == 2 || *HY - *TY == -2)) {
        (*TX) += (*TX < *HX) ? 1 : -1;
        (*TY) += (*TY < *HY) ? 1 : -1;
        return;
    }

    if (*HX - 2 == *TX) {
        (*TX)++; // Note: this is not the same as *TX++, but IS the same as *TX = *TX + 1;
        *TY = *HY;
    } else if (*HX + 2 == *TX) {
        (*TX)--;
        *TY = *HY;
    } else if (*HY - 2 == *TY) {
        (*TY)++;
        *TX = *HX;
    } else if (*HY + 2 == *TY) {
        (*TY)--;
        *TX = *HX;
    }
}

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 9\\input.txt", "r");
    char** matrix = calloc(1000, sizeof(char) * 1000);

    for (int i = 0; i < 1000; i++) {
        matrix[i] = calloc(1000, sizeof(char));
    }

    const int nodesCount = 10;
    int** nodes = calloc(nodesCount, sizeof(int*) * 2);

    // All knots start at coordinates (500, 500)
    for (int i = 0; i < nodesCount; i++) {
        nodes[i] = calloc(2, sizeof(int*));
        nodes[i][0] = 500;
        nodes[i][1] = 500;
    }

    matrix[500][500] = '#';

    char line[10] = "";
    char* token;
    char command[2];
    int amountToMove;

    while (fgets(line, sizeof(line), fptr)) {
        token = strtok(line, " ");
        strcpy(command, token);
        token = strtok(NULL, "\n");
        amountToMove = atoi(token);


        for (int t = 0; t < amountToMove; t++) {

            if (strcmp(command, "L") == 0) {
                nodes[0][0]--; // Head x coordinate
            } else if (strcmp(command, "R") == 0) {
                nodes[0][0]++; // Head x coordinate
            } else if (strcmp(command, "U") == 0) {
                nodes[0][1]--; // Head y coordinate
            } else if (strcmp(command, "D") == 0) {
                nodes[0][1]++; // Head y coordinate
            }

            for (int k = 1; k < nodesCount; k++) {
                moveTailIfNeeded(k, nodes);
            }

            // Mark the position of the last knot
            matrix[nodes[nodesCount - 1][0]][nodes[nodesCount - 1][1]] = '#';
        }
    }

    int uniquePositionsVisited = 0;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (matrix[i][j] == '#') {
                uniquePositionsVisited++;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("x: %d, y: %d\n", nodes[i][0], nodes[i][1]);
    }

    printf("\nUnique positions visited: %d\n", uniquePositionsVisited);

    return 0;
}
