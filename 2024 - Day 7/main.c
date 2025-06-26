#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "../../C-headers/_strings.h"

size_t numbers_count;

int is_doable(int* numbers, uint64_t target, uint32_t last_index, FILE* output_file) {
    int last = numbers[last_index];
    fprintf(output_file, "Checking target: %lu, last: %d", target, last);

    if (last_index == 0) {
        fprintf(output_file, " -> Last and %d\n", target == last);
        return target == last;
    }

    int can_divide = 0, can_subtract = 0, check_subtract = 0, check_concat = 0;
    if (target % last == 0) {
        fprintf(output_file, " -> Divisible and not done: %lu / %d\n", target, last);
        if (!is_doable(numbers, target / last, last_index - 1, output_file)) {
            if (!is_doable(numbers, target - last, last_index - 1, output_file)) {
                check_concat = 1;
            }
            can_subtract = 1;
        }
        can_divide = 1;
    } else {
        fprintf(output_file, " -> Not divisible, checking subtraction %lu - %d\n", target, last);
        if (is_doable(numbers, target - last, last_index - 1, output_file)) {
            return 1;
        }
        check_concat = 1;
    } 

    if ((can_divide == 1 || can_subtract == 1) && check_concat == 0) return 1;

    if (check_concat == 1) {
        char* last_str = calloc(20, sizeof(char));
        snprintf(last_str, 20, "%d", last);
        char* target_str = calloc(20, sizeof(char));
        snprintf(target_str, 20, "%lu", target);

        int last_len = strlen(last_str) - 1;
        int target_ends_with_last = 1;
        for (int i = strlen(target_str) - 1; i > 0; i--) {
            if (last_len < 0) break;
            if (target_str[i] != last_str[last_len]) {
                target_ends_with_last = 0;
                break;
            }
            last_len--;
        }
        if (target_ends_with_last == 0) {
            fprintf(output_file, " -> Checking concat. Target: %lu doesn't end with last: %d\n", target, last);
            return 0;
        }

        target_str[strlen(target_str) - strlen(last_str)] = '\0';
        uint64_t new_target = atoll(target_str);
        fprintf(output_file, " -> Checking concat. Target: %lu ends with last: %d. Remainder %lu\n", target, last, new_target);
        return is_doable(numbers, new_target, last_index - 1, output_file);
    }
    return 0;
}

int main() {
    clock_t start_time = clock();
    FILE* fptr = fopen("input.txt", "r");
    
    char* token;
    uint64_t total = 0;
    uint64_t target;
    uint32_t last;
    int* numbers;
    char line[50];

    FILE* debug_file = fopen("test_output.txt", "w");

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

    double total_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %f\n", total_time);
    return 0;
}
