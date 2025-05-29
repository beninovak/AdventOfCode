#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../C-headers/read_file.h"
#include "../../C-headers/_strings.h"

int get_diff(int a, int b) {
    int diff = a - b;
    return diff < 0 ? diff * -1 : diff;
}

int is_line_unsafe(char** tokens, int skip_index, int num_count) {
    int previous = 0, current = 0, diff = 0, direction = 0;
    int unsafe = 0, count = 0;

    for(int i = 0; i < num_count; i++) {
        if (i == skip_index) continue;
        current = atoi(tokens[i]);
        printf("%d ", current);

        if (count == 0) {
            previous = current;
            count++;
            continue;
        }

        int diff = current - previous;
        if (diff < 0) {
            diff = diff * -1;
        }
        if (diff < 1 || diff > 3) {
            printf(" - Big diff or same");
            unsafe = 1;
            break; 
        }

        if (count > 1) {
            if ((direction == -1 && current > previous) || 
                (direction == 1 && current < previous)
            ) {
                printf(" - Wrong direction");
                unsafe = 1;
                break;
            }

        }

        if (current < previous) {
            direction = -1;
        } else {
            direction = 1;
        }

                     
        previous = current;
        count++;
    }

    printf("\n");
    if (unsafe == 1 && skip_index == -1) {
        for(int i = 0; i < num_count; i++) {
            if (is_line_unsafe(tokens, i, num_count) == 0) {
                unsafe = 0;
                printf("Newly safe ^\n");
                break;
            }
        }
    }
    return unsafe;
}

int main () {

    FILE* fptr = fopen("input.txt", "rb");
    if (fptr == NULL) {
        printf("Cannot open file!\n");
        return 1;
    }
    
    _file* file = file_read(fptr);

    int safe_reports = 0;
    for(int i = 0; i < file->line_count; i++) {
        _tokens* tokens = _strings_tokenize(file->lines[i]->start, ' ');
        if(is_line_unsafe(tokens->tokens, -1, tokens->size) == 0) {
            safe_reports++; 
        }
        _tokens_free(tokens);
    }
    _file_free(file);
    
    printf("\nSafe reports: %d\n", safe_reports);
    return 0;
}
