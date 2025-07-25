//#include "../../C-*headers/file_read.h";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {

    FILE* fptr = fopen("input.txt", "rb");
    int line_length = 1;

    while(fgetc(fptr) != '\n') {
       line_length++;
    }
    line_length++;
    rewind(fptr);

    char* line = calloc(line_length, sizeof(char));

    int rows = 0;
    int num1 = 0;
    int num2 = 0;

    while(fgets(line, line_length, fptr)) {
        rows++;
    }
    rewind(fptr);

    char* token;
    int* left = calloc(rows, sizeof(int));
    int* right = calloc(rows, sizeof(int));
    int count = 0;
    while(fgets(line, line_length, fptr)) {
        token = strtok(line, " ");
        num1 = atoi(token);
        token = strtok(NULL, "\n");
        num2 = atoi(token);
        left[count] = num1;
        right[count] = num2;
        count++;
    }
    fclose(fptr);

    qsort(left, rows, sizeof(int), compare);
    qsort(right, rows, sizeof(int), compare);

    int sum_diffs = 0;
    long similarity_score = 0;
    for(int i = 0; i < rows; i++) {
        int diff = left[i] - right[i];
        if (diff < 0) {
            diff = diff * -1;
        }
        sum_diffs = sum_diffs + diff;
        
        int count = 0;

        for(int j = 0; j < rows; j++) {
            if (left[i] == right[j]) {
                count++;
            }
        }
        similarity_score = similarity_score + (left[i] * count);
        //printf("Similarity: %ld\n", similarity_score);
    }

    printf("Done. Sum diffs: %d\n", sum_diffs);
    printf("Done. Similarity score: %ld\n", similarity_score);
    return 0;
}
