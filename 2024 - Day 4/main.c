#include <stdio.h>
#include <string.h>
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
            if (grid[r][c] == 'X') {
                printf("Found x: [%d, %d]\n", r, c);
                too_close_to_left = too_close_to_right = too_close_to_top = too_close_to_bottom = 0;
                if (r - 3 < 0) {
                    too_close_to_top = 1;
                }
                if (r + 3 > rows - 1) {
                    too_close_to_bottom = 1;
                }
                if (c - 3 < 0) {
                    too_close_to_left = 1;
                }
                if (c + 3 > columns - 1) {
                    too_close_to_right = 1;
                }

                // Check top
                if (too_close_to_top == 0 && grid[r-1][c] == 'M' && grid[r-2][c] == 'A' && grid[r-3][c] == 'S') {
                    xmas_count++;
                }

                // Check bottom
                if (too_close_to_bottom == 0 && grid[r+1][c] == 'M' && grid[r+2][c] == 'A' && grid[r+3][c] == 'S') {
                    xmas_count++;
                }

                if (too_close_to_left == 0) {
                    if (grid[r][c-1] == 'M' && grid[r][c-2] == 'A' && grid[r][c-3] == 'S') {
                        xmas_count++;
                    }
                    if (too_close_to_top == 0 && grid[r-1][c-1] == 'M' && grid[r-2][c-2] == 'A' && grid[r-3][c-3] == 'S') {
                        xmas_count++;
                    }
                    if (too_close_to_bottom == 0 && grid[r+1][c-1] == 'M' && grid[r+2][c-2] == 'A' && grid[r+3][c-3] == 'S') {
                        xmas_count++;
                    }
                }

                if (too_close_to_right == 0) {
                    if (grid[r][c+1] == 'M' && grid[r][c+2] == 'A' && grid[r][c+3] == 'S') {
                        xmas_count++;
                    }
                    if (too_close_to_top == 0 && grid[r-1][c+1] == 'M' && grid[r-2][c+2] == 'A' && grid[r-3][c+3] == 'S') {
                        xmas_count++;
                    }
                    if (too_close_to_bottom == 0 && grid[r+1][c+1] == 'M' && grid[r+2][c+2] == 'A' && grid[r+3][c+3] == 'S') {
                        xmas_count++;
                    }
                }

            }
        }
    }
    printf("XMAS COUNT: %d\n", xmas_count);
    return 0;
}
