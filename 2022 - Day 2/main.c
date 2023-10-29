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

        if (player1 == 'A') {

            switch (player2) {
                case 'X':
                    score += 3;
                    break;

                case 'Y':
                    score += 4;
                    break;

                case 'Z':
                    score += 8;
                    break;
            }

        } else if (player1 == 'B') {

            switch (player2) {
                case 'X':
                    score += 1;
                    break;

                case 'Y':
                    score += 5;
                    break;

                case 'Z':
                    score += 9;
                    break;
            }

        } else if (player1 == 'C') {

            switch (player2) {
                case 'X':
                    score += 2;
                    break;

                case 'Y':
                    score += 6;
                    break;

                case 'Z':
                    score += 7;
                    break;
            }
        }
    }

    printf("Final score: %ld\n", score);
    return 0;
}
