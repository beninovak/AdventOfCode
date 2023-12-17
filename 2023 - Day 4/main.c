#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 4\\input.txt", "r");

    char line[200] = "";
    char* token;

    int gameId = 0;
    int cards[200] = {0};
    int cardsArrayLength = sizeof(cards) / sizeof(cards[0]);
    int winningNumbers[50] = {0};
    int scratchedNumbers[50] = {0};
    int index, readWinningNumbers;

    int cardScoreSum = 0;

    while (fgets(line, sizeof(line), fptr)) {

        cards[gameId]++;
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

        for (int l = 0; l < cards[gameId]; l++) {
            for(int c = gameId + 1; c < gameId + 1 + winningNumbersCount; c++) {
                if (c < cardsArrayLength) {
                    cards[c] = cards[c] + 1;
                }
            }
        }

        cardScoreSum += cardScore;

        gameId++;
    }

    fclose(fptr);

    int totalCards = 0;

    for (int i = 0; i < cardsArrayLength; i++) {
        totalCards += cards[i];
    }

    printf("Total cards: %d\n", totalCards);
    printf("Card score sum: %d", cardScoreSum);

    return 0;
}
