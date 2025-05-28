#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../C-headers/read_file.h"

int get_diff(int a, int b) {
    int diff = a - b;
    return diff < 0 ? diff * -1 : diff;
}

int is_line_unsafe(char* line, int skip_index) {

    int num_count = 0;
    for(int i = 0; i < strlen(line); i++) {
        if (line[i] == ' ') {
            num_count++;
        }
    }
    char** tokens = calloc(num_count, sizeof(char*));
    char* token;
    for(int i = 0; i < num_count; i++) {
        if (i == 0) {
            token = strtok(line, " \n"); 
        } else {
            token = strtok(NULL, " \n");
        }
        tokens[i] = calloc(strlen(token), sizeof(char));
        strcpy(tokens[i], token);
    }


    int previous = 0, current = 0, diff = 0, direction = 0;
    int unsafe = 0, count = 0;

    for(int i = 0; i < num_count; i++) {
        if (i == skip_index) continue;
        current = atoi(tokens[i]);
        printf("%d ", current);

        if (count == 0) {
            previous = current;
            token = strtok(NULL, " \n");
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
        token = strtok(NULL, " \n");
        count++;
    }

    if (unsafe == 1 && skip_index == -1) {

    }
    printf("\n");
    return unsafe;
}

int main () {

    FILE* fptr = fopen("example.txt", "rb");
    if (fptr == NULL) {
        printf("Cannot open file!\n");
        return 1;
    }
    
    _file* file = file_read(fptr);

    int safe_reports = 0;
    for(int i = 0; i < file->line_count; i++) {
        if(is_line_unsafe(file->lines[i]->start, -1) == 0) {
            safe_reports++; 
        } else {
            // TODO - Split line into
        }
    }
    
    printf("\nSafe reports: %d\n", safe_reports);
    return 0;
}
