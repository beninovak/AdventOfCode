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

    int viewDistance;
    int currentScenicScore = 1;
    int maxScenicScore = 1;

    // Start at second row, end on penultimate row
    for (int i = 2; i < rows - 1; i++) {
        // Don't check first and last column
        for (int j = 4; j < columns - 2; j++) {

            viewDistance = 0;
            currentScenicScore = 1;

            // Check left
            for (int k = j - 1; k >= 0; k--) {
                viewDistance++;
                if (matrix[i][k] >= matrix[i][j]) {
                    break;
                }
            }

            currentScenicScore *= viewDistance;
            viewDistance = 0;

            // Check right
            for (int k = j + 1; k < columns - 1; k++) {
                viewDistance++;
                if (matrix[i][k] >= matrix[i][j]) {
                    break;
                }
            }

            currentScenicScore *= viewDistance;
            viewDistance = 0;

            // Check top
            for (int k = i - 1; k >= 0; k--) {
                viewDistance++;
                if (matrix[k][j] >= matrix[i][j]) {
                    break;
                }
            }

            currentScenicScore *= viewDistance;
            viewDistance = 0;

            // Check bottom
            for (int k = i + 1; k < rows; k++) {
                viewDistance++;
                if (matrix[k][j] >= matrix[i][j]) {
                    break;
                }
            }

            currentScenicScore *= viewDistance;

            if (currentScenicScore > maxScenicScore) {
                maxScenicScore = currentScenicScore;
            }
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nMax scenic score of any tree: %d", maxScenicScore);
    printf("\nTime taken for task: %f", cpu_time_used);

    return 0;
}
