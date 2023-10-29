#include <stdio.h>
#include <string.h>

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 2\\input.txt", "r");
    char line[4]; // Letter-space-letter-newline

    char player1;
    char player2;
    char outcome[4];
    long score = 0;

    while(fgets(line, 4, fptr)) {

        if (line[0] == '\n') continue;

        player1 = line[0];
        player2 = line[2];

        if (player2 == 'X') {

            score += 1;
            if (player1 == 'A') {
                score += 3;
            } else if (player1 == 'C') {
                score += 6;
            }
        } else if (player2 == 'Y') {

            score += 2;
            if (player1 == 'A') {
                score += 6;
            } else if (player1 == 'B') {
                score += 3;
            }

        } else if (player2 == 'Z') {

            score += 3;
            if (player1 == 'B') {
                score += 6;
            } else if (player1 == 'C') {
                score += 3;
            }
        }
    }

    printf("Final score: %ld\n", score);
    return 0;
}
