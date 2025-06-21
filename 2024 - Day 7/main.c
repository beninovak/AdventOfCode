#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../../C-headers/_strings.h"
#include "../../C-headers/file_read.h"

int is_doable(_tokens* toks, uint64_t target, uint32_t last_index) {
    // char* endptr;
    // uint64_t last = strtoul(toks->tokens[last_index], &endptr, 10);
    uint64_t last = atoll(toks->tokens[last_index]);
    printf("Checking target: %lu, last: %lu", target, last);
    if (target % last != 0) {
        if (last_index > 1) {
            printf(" -> Not divisible, checking subtraction!\n");
            return is_doable(toks, target - last, last_index - 1);
        } else if (target == last) {
            printf(" -> Last not divisible and good!\n");
            return 1;
        }
        printf(" -> Not divisible, returning cuz last!\n");
        return 0;
    } else if (last_index > 1) {
        printf(" -> Divisible and not done!\n");
        return is_doable(toks, target / last, last_index - 1);
    } else if (target == last) {
        printf(" -> Last and good!\n");
        return 1;
    }
    return 0;
}

int main() {

    FILE* fptr = fopen("input.txt", "rb");
    _file* file = file_read(fptr);
    fclose(fptr);
    
    char* ch;
    uint64_t total = 0;
    uint64_t target;
    uint32_t last;
    // char* endptr;

    for(int i = 0; i < file->line_count; i++) {

        _tokens* toks = _string_tokenize(file->lines[i]->start, ' ');
        toks->tokens[0][strlen(toks->tokens[0]) - 1] = '\0'; // Removes ':' from the end of the first number.
        // target = strtoul(toks->tokens[0], &endptr, 10);
        target = atoll(toks->tokens[0]);

        uint32_t last_index = toks->size - 1;

        if (is_doable(toks, target, last_index)) {
            total += target;
        }
        printf("\n---------------------- New total: %lu ----------------------\n\n", total);

        _tokens_free(toks);
    }

    _file_free(file);
    printf("\nTotal: %lu\n", total);
    return 0;
}
