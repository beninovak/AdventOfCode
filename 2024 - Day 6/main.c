#include <stdio.h>
#include <stdlib.h>
#include "../../C-headers/read_file.h"

int positions_count = 64;
int** visited_positions;
int visited_positions_count;

void walk_guard(_file* file, int Y, int X, int direction, int column_width) {
    char ch;
    int guard_out_of_bounds = 0;
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
                visited_positions[visited_positions_count][2] = direction;
                visited_positions_count++;

                if (visited_positions_count == positions_count) {
                    positions_count *= 2;
                    visited_positions = realloc(visited_positions, positions_count * sizeof(int*));
                    if (visited_positions == NULL) {
                        printf("Bl bula brt!");
                    } else {
                        for(int r = visited_positions_count; r < positions_count; r++) {
                            visited_positions[r] = calloc(3, sizeof(int));
                        }
                    }
                }
            }
        }
    }
}

int walk_guard_obstacle(_file* file, int Y, int X, int direction, int column_width) {
    int count = 0;
    char ch;
    int guard_out_of_bounds = 0;
    while(count < 10000) {
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

        if (guard_out_of_bounds == 1) return 0; // Meaning there was no infinite loop.

        ch = file->lines[Y]->start[X];
        if (ch == '#') {
            switch(direction) {
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
        } 
        count++;
    }
    return 1;
}

int main() {

    FILE* fptr = fopen("input.txt", "rb");
    _file* file = file_read(fptr);
    fclose(fptr);

    visited_positions = calloc(positions_count, sizeof(int*));
    for (int i = 0; i < positions_count; i++) {
        visited_positions[i] = calloc(3, sizeof(int));
    }

    int X, Y;
    visited_positions_count = 0;
    for(int i = 0; i < file->line_count; i++) {
        for(int j = 0; j < file->lines[i]->size; j++) {
            if(file->lines[i]->start[j] == '^') {
                visited_positions[0][0] = i;
                visited_positions[0][1] = j;
                visited_positions[0][2] = 1;
                Y = i;
                X = j;
                visited_positions_count = 1;
            }
        }
    }

    int column_width = file->lines[0]->size;

    // direction 1 is up, -1 is down, 2 is right, -2 is left.
    walk_guard(file, Y, X, 1, column_width);

    printf("\nVisited positions: %d\n", visited_positions_count);
    
    int possible_locations_for_obstacle = 0;
    for(int i = 0; i < visited_positions_count - 1; i++) { 
        // Start at the second visited position. Can't change first as per task description.
        // Also don't check the last elements, as the last one has no next element to check.

        if (visited_positions[0][0] == visited_positions[i+1][0] && visited_positions[0][1] == visited_positions[i+1][1]) continue;

        file->lines[visited_positions[i+1][0]]->start[visited_positions[i+1][1]] = '#';
        if (walk_guard_obstacle(file, visited_positions[i][0], visited_positions[i][1], visited_positions[i][2], column_width) == 1) {
            possible_locations_for_obstacle++;
            printf("\n%d %d", visited_positions[i+1][0], visited_positions[i+1][1]);
        }
        file->lines[visited_positions[i+1][0]]->start[visited_positions[i+1][1]] = '.';
    }

    free(visited_positions);
    printf("\nValid obstacle positions: %d\n", possible_locations_for_obstacle);
    return 0;
}
