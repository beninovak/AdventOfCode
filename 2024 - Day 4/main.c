#include <stdio.h>
#include "../../C-headers/read_file.h"

int main() {

    FILE* fptr = fopen("input.txt", "rb");
    int rows = file_read_get_lines(fptr);
    int columns = 0;

    char ch;
    while((ch = fgetc(fptr)) != EOF) {
        if (ch != '\n') {
            columns++;
        } else {
            break;
        }
    }
    rewind(fptr);

    char** grid = calloc(rows, sizeof(char*));
    for(int i = 0; i < rows; i++) {
        grid[i] = calloc(columns, sizeof(char));
    }

    int current_row = 0;
    int current_column = 0;
    while((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            current_row++;
            current_column = 0;
            continue;
        }
        grid[current_row][current_column] = ch;
        current_column++;
    }

    int xmas_count = 0;
    int too_close_to_left, too_close_to_right, too_close_to_top, too_close_to_bottom;
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < columns; c++) {
            if (grid[r][c] == 'M') {
                printf("Found x: [%d, %d]\n", r, c);
                too_close_to_left = too_close_to_right = too_close_to_top = too_close_to_bottom = 0;
                if (r - 2 < 0) {
                    too_close_to_top = 1;
                }
                if (r + 2 > rows - 1) {
                    too_close_to_bottom = 1;
                }
                if (c - 2 < 0) {
                    too_close_to_left = 1;
                }
                if (c + 2 > columns - 1) {
                    too_close_to_right = 1;
                }

                if (too_close_to_left == 0 && too_close_to_top == 0) {
                    char bottom_left_char = grid[r][c-2];
                    char top_right_char = grid[r-2][c];
                    if (
                        !(bottom_left_char == top_right_char ||
                        grid[r-1][c-1] != 'A' || grid[r-2][c-2] != 'S' || 
                        (bottom_left_char != 'S' && bottom_left_char != 'M') || (top_right_char != 'S' && top_right_char != 'M')
                    )) {
                        xmas_count++;
                    }
                }
                
                if (too_close_to_left == 0 && too_close_to_bottom == 0) {
                    char top_left_char = grid[r][c-2];
                    char bottom_right_char = grid[r+2][c];
                    if (
                        !(bottom_right_char == top_left_char ||
                        grid[r+1][c-1] != 'A' || grid[r+2][c-2] != 'S' || 
                        (bottom_right_char != 'S' && bottom_right_char != 'M') || (top_left_char != 'S' && top_left_char != 'M')
                    )) {
                        xmas_count++;
                    }
                }

                if (too_close_to_right == 0 && too_close_to_top == 0) {
                    char top_left_char = grid[r-2][c];
                    char bottom_right_char = grid[r][c+2];
                    if (
                        !(bottom_right_char == top_left_char ||
                        grid[r-1][c+1] != 'A' || grid[r-2][c+2] != 'S' || 
                        (bottom_right_char != 'S' && bottom_right_char != 'M') || (top_left_char != 'S' && top_left_char != 'M')
                    )) {
                        xmas_count++;
                    }
                }

                if (too_close_to_right == 0 && too_close_to_bottom == 0) {
                    char bottom_left_char = grid[r+2][c];
                    char top_right_char = grid[r][c+2];
                    if (
                        !(top_right_char == bottom_left_char ||
                        grid[r+1][c+1] != 'A' || grid[r+2][c+2] != 'S' || 
                        (top_right_char != 'S' && top_right_char != 'M') || (bottom_left_char != 'S' && bottom_left_char != 'M')
                    )) {
                        xmas_count++;
                    }
                }
            }
        }
    }
    printf("XMAS COUNT: %d\n", xmas_count / 2); // Divided by 2 cuz otherwise every X-MAS is counted twice.
    return 0;
}
