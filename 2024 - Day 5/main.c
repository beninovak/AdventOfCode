#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../C-headers/read_file.h"
#include "../../C-headers/_strings.h"

int main() {

    FILE* fptr = fopen("example.txt", "rb");
    _file* file = file_read(fptr);
    fclose(fptr);

    int** page_order_rules;
    int continue_from;
    for(int i = 0; i < file->line_count; i++) {
        if (file->lines[i]->size == 1 && file->lines[i]->start[0] == '\n') {
            page_order_rules = calloc(i, sizeof(int*));
            continue_from = i + 1;
            break;
        }
    }

    char* token;
    for(int i = 0; i < continue_from - 1; i++) {
        page_order_rules[i] = calloc(2, sizeof(int));
        token = strtok(file->lines[i]->start, "|");
        page_order_rules[i][0] = atoi(token);
        token = strtok(NULL, "\n");
        page_order_rules[i][1] = atoi(token);
        token = NULL;
    }

    long corrent_updates_sum = 0;
    long incorrent_updates_sum = 0;
    int token_rows = file->line_count - continue_from;
    _tokens** tokens = (_tokens**)calloc(token_rows, sizeof(_tokens*));
    for(int i = 0; i < token_rows; i++) {
        tokens[i] = _strings_tokenize(file->lines[continue_from + i]->start, ',');
        
        int is_valid = 1;
        for(int t = 0; t < tokens[i]->size - 1; t++) {
            int num1 = atoi(tokens[i]->tokens[t]);
            int num2 = atoi(tokens[i]->tokens[t+1]);

            for(int p = 0; p < continue_from - 1; p++) {
                if (page_order_rules[p][1] == num1 && page_order_rules[p][0] == num2) { // If numbers are in the wrong order
                    is_valid = 0;
                    // TODO - reorder all incorrect updates, not just two tokens at a time. qsort??
                    //break;
                    // char* temp = calloc(tokens[i]->size, sizeof(char));
                    // strcpy(temp, tokens[i]->tokens[t]);
                    // strcpy(tokens[i]->tokens[t], tokens[i]->tokens[t+1]);
                    // strcpy(tokens[i]->tokens[t+1], temp);
                    // free(temp);
                }
            }
            // if (is_valid == 0) break;
        }

        if (is_valid == 1) {
            printf("Corrent: %d - %s\n", (tokens[i]->size / 2) + 1, tokens[i]->tokens[(tokens[i]->size / 2)]);
            corrent_updates_sum += atoi(tokens[i]->tokens[(tokens[i]->size / 2)]); // Add middle tokens
        } else {
            printf("Incorrect: %d - %s\n", (tokens[i]->size / 2) + 1, tokens[i]->tokens[(tokens[i]->size / 2)]);
            incorrent_updates_sum += atoi(tokens[i]->tokens[(tokens[i]->size / 2)]); // Add middle tokens
        }
        _tokens_free(tokens[i]);
    }
    free(tokens);

    _file_free(file);

    printf("\nCorrect sum: %lu\n", corrent_updates_sum);
    printf("\nIncorrect sum: %lu\n", incorrent_updates_sum);
    return 0;
}
