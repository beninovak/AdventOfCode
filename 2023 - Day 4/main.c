#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 4\\input.txt", "r");

    char line[200] = "";
    char* token;

    int winningNumbers[50] = {0};
    int scratchedNumbers[50] = {0};
    int index, readWinningNumbers;

    int cardScoreSum = 0;

    while (fgets(line, sizeof(line), fptr)) {

        index = readWinningNumbers = 0;
        token = strtok(line, ":");

        token = strtok(NULL, " \n");
        while (token != NULL) {

            if (*token == '|') {
                readWinningNumbers = 1;
                index = 0;
            } else {
                if (readWinningNumbers) {
                    scratchedNumbers[index] = atoi(token);
                } else {
                    winningNumbers[index] = atoi(token);
                }

                index++;
            }
            token = strtok(NULL, " \n");
        }

        int i = 0, j, cardScore = 0, winningNumbersCount = 0;
        while (scratchedNumbers[i] != 0) {
            j = 0;
            while (winningNumbers[j] != 0) {
                if (scratchedNumbers[i] == winningNumbers[j]) {
                    winningNumbersCount++;
                    if (winningNumbersCount == 1) {
                        cardScore = 1;
                    } else {
                        cardScore = cardScore * 2;
                    }
                    break;
                }
                j++;
            }
            i++;
        }
        cardScoreSum += cardScore;
    }

    fclose(fptr);

    printf("Card score sum: %d", cardScoreSum);

    return 0;
}
