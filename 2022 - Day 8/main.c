#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 8\\input.txt", "r");
    int rows = 0;
    char line[101] = "";

    while (fgets(line, sizeof(line), fptr)) {
        rows++;
    }

    rewind(fptr);

    int columns = (int)strlen(line);
    int** matrix = calloc(rows, sizeof(int*));

    for (int i = 0; i < rows; i++) {

        matrix[i] = calloc(columns, sizeof(int*));
        fgets(line, sizeof(line), fptr);

        for (int j = 0; j < columns - 1; j++) {
            if (line[j] != '\n') {
                matrix[i][j] = line[j] - '0';
            }
        }
    }

    int isVisible;
    int visibleTrees = (2 * (columns - 1)) + (2 * (rows - 2));

    // Start at second row, end on penultimate row
    for (int i = 1; i < rows - 1; i++) {
        // Don't check first and last column
        for (int j = 1; j < columns - 2; j++) {

            isVisible = 1;

            // Check left
            for (int k = 0; k < j; k++) {
                if (matrix[i][k] >= matrix[i][j]) {
                    isVisible = 0;
                    break;
                }
            }

            if (isVisible == 1) {
                visibleTrees++;
                continue;
            }

            isVisible = 1;

            // Check right
            for (int k = columns - 2; k > j; k--) {
                if (matrix[i][k] >= matrix[i][j]) {
                    isVisible = 0;
                    break;
                }
            }

            if (isVisible == 1) {
                visibleTrees++;
                continue;
            }

            isVisible = 1;

            // Check top
            for (int k = 0; k < i; k++) {
                if (matrix[k][j] >= matrix[i][j]) {
                    isVisible = 0;
                    break;
                }
            }

            if (isVisible == 1) {
                visibleTrees++;
                continue;
            }

            isVisible = 1;

            // Check bottom
            for (int k = rows - 1; k > i; k--) {
                if (matrix[k][j] >= matrix[i][j]) {
                    isVisible = 0;
                    break;
                }
            }

            if (isVisible == 1) {
                visibleTrees++;
                continue;
            }
        }
    }


//    for (int k = 0; k < rows; k++) {
//        for (int l = 0; l < columns - 1; l++) {
//           printf("%d ", matrix[k][l]);
//        }
//        printf("\n");
//    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nVisible trees: %d", visibleTrees);
    printf("\nTime taken for task: %f", cpu_time_used);

    return 0;
}
