#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../../C-headers/_strings.h"

int is_doable(int* numbers, uint64_t target, uint32_t last_index, FILE* output_file) {
    int last = numbers[last_index];
    fprintf(output_file, "Checking target: %lu, last: %d", target, last);

    if (last_index == 0) {
        fprintf(output_file, " -> Last and %d\n", target == last);
        return target == last;
    }

    if (target % last == 0) {
        fprintf(output_file, " -> Divisible and not done!\n");
        if (!is_doable(numbers, target / last, last_index - 1, output_file)) {
            return is_doable(numbers, target - last, last_index - 1, output_file);
        }
        return 1;
    } else  {
        fprintf(output_file, " -> Not divisible, checking subtraction!\n");
        return is_doable(numbers, target - last, last_index - 1, output_file);
    } 
    fprintf(output_file, "\nReturning at bottom!\n");
    return 0;
}

int main() {
    FILE* fptr = fopen("input.txt", "r");
    
    char* token;
    uint64_t total = 0;
    uint64_t target;
    uint32_t last;
    int* numbers;
    size_t numbers_count;
    char line[50];

    FILE* debug_file = fopen("output.txt", "w");

    while(fgets(line, sizeof(line), fptr) != NULL) {
        numbers_count = _string_count_occurrences(line, ' ');
        token = strtok(line, ": ");
        target = atoll(token);

        numbers = calloc(numbers_count, sizeof(int));
        uint32_t count = 0;
        token = strtok(NULL, " \n");
        while(token != NULL) {
            numbers[count] = atoi(token);
            token = strtok(NULL, " \n");
            count++;
        }
        uint32_t last_index = numbers_count - 1;

        for(int i = 0; i < numbers_count; i++) {
            fprintf(debug_file, "%d ", numbers[i]);
        }
        fprintf(debug_file, "\n");
        if (is_doable(numbers, target, last_index, debug_file)) {
            total += target;
        }
        fprintf(debug_file, "\n---------------------- New total: %lu ----------------------\n\n", total);

        free(numbers);
    }
 
    fprintf(debug_file, "\nTotal: %lu\n", total);
    printf("\nTotal: %lu\n", total);
    fclose(fptr);
    return 0;
}
