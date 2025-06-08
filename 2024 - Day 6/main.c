#include <stdio.h>
#include <stdlib.h>
#include "../../C-headers/read_file.h"

int main() {

    FILE* fptr = fopen("input.txt", "rb");
    _file* file = file_read(fptr);
    fclose(fptr);

    int positions_count = 64;
    int** visited_positions = calloc(positions_count, sizeof(int*));
    for (int i = 0; i < positions_count; i++) {
        visited_positions[i] = calloc(2, sizeof(int));
    }

    int X, Y;
    int visited_positions_count = 0;
    for(int i = 0; i < file->line_count; i++) {
        for(int j = 0; j < file->lines[i]->size; j++) {
            if(file->lines[i]->start[j] == '^') {
                visited_positions[0][0] = i;
                visited_positions[0][1] = j;
                Y = i;
                X = j;
                visited_positions_count = 1;
            }
        }
    }
    

    int column_width = file->lines[0]->size;
    int direction = 1; // 1 is up, -1 is down, 2 is right, -2 is left.
    int guard_out_of_bounds = 0;
    char ch;
    while(1) {
        switch(direction) {
            case 1:
                Y--;
                if (Y < 0) guard_out_of_bounds = 1;
                break;

            case -1:
                Y++;
                if (Y >= file->line_count) guard_out_of_bounds = 1;
                break;

            case 2:
                X++;
                if (X >= column_width) guard_out_of_bounds = 1;
                break;

            case -2:
                X--;
                if (X < 0) guard_out_of_bounds = 1;
                break;
        }

        if (guard_out_of_bounds == 1) break;

        ch = file->lines[Y]->start[X];
        if (ch == '#') {
            switch(direction)     {
                case 1:
                    Y++;
                    direction = 2;
                    break;

                case -1:
                    Y--;
                    direction = -2;
                    break;

                case 2:
                    X--;
                    direction = -1;
                    break;

                case -2:
                    X++;
                    direction = 1;
                    break;
            }
        } else {
            int repeated_position = 0;
            for(int i = 0; i < visited_positions_count; i++) {
                if (Y == visited_positions[i][0] && X == visited_positions[i][1]) {
                    repeated_position = 1; 
                }
            }

            if (repeated_position == 0) {
                printf("\n%d %d", Y, X);
                visited_positions[visited_positions_count][0] = Y;
                visited_positions[visited_positions_count][1] = X;
                visited_positions_count++;

                if (visited_positions_count == positions_count) {
                    positions_count *= 2;
                    visited_positions = realloc(visited_positions, positions_count * sizeof(int*));
                    if (visited_positions == NULL) {
                        printf("Bl bula brt!");
                    } else {
                        for(int r = visited_positions_count; r < positions_count; r++) {
                            visited_positions[r] = calloc(2, sizeof(int));
                        }
                        // free(val);
                    }
                }
            }
        }
    }

    free(visited_positions);
    printf("\nVisited positions: %d\n", visited_positions_count);
    return 0;
}
