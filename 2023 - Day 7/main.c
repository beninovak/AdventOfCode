#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The weakest hand has the smallest rank
enum HandRank {
    FIVE_OF_A_KIND = 6,
    FOUR_OF_A_KIND = 5,
    FULL_HOUSE = 4,
    THREE_OF_A_KIND = 3,
    TWO_PAIR = 2,
    ONE_PAIR = 1,
    HIGH_CARD = 0,
};

int isHandFiveOfAKind(const char hand[10]) {
    char one = hand[0];
    for (int i = 1; i < 5; i++) {
        if (hand[i] != one) return 0;
    }
    return 1;
}


int isHandFourOfAKind(const char hand[10]) {

    // Handles case when the first card is the odd one out, and the other four are all the same
    if ((hand[0] != hand[1]) && hand[1] == hand[2] && hand[1] == hand[3] && hand[1] == hand[4]) return 1;

    char one = hand[0];
    int matchingChars = 0, notMatchingChars = 0;

    // Start at second card
    for (int i = 1; i < 5; i++) {
        if (hand[i] == one) {
            matchingChars++;
        } else {
            notMatchingChars++;
        }
    }

    if (matchingChars == 3 && notMatchingChars == 1) return 1;

    return 0;
}


int isHandFullHouse(const char hand[10]) {
    char one = hand[0];
    int matchingChars = 0, notMatchingChars = 0;
    int notMatchingCharsIndexes[4] = { 0 };
    int index = 0;

    for (int i = 1; i < 5; i++) {
        if (hand[i] == one) {
            matchingChars++;
        } else {
            notMatchingChars++;
            notMatchingCharsIndexes[index] = i;
            index++;
        }
    }

    // Hand is full house when two cards match and two don't, and the two that don't are the same OR
    // when 1 matches and 3 don't, and the three that don't are the same
    if (matchingChars == 2 && notMatchingChars == 2) {
        if (hand[notMatchingCharsIndexes[0]] == hand[notMatchingCharsIndexes[1]]) return 1;
    } else if (matchingChars == 1 && notMatchingChars == 3) {
        if (hand[notMatchingCharsIndexes[0]] == hand[notMatchingCharsIndexes[1]] && hand[notMatchingCharsIndexes[0]] == hand[notMatchingCharsIndexes[2]]) {
            return 1;
        }
    }

    return 0;
}

int isHandThreeOfAKind(const char hand[10]) {
    char one = hand[0];
    int matchingChars = 0, notMatchingChars = 0;
    int notMatchingCharsIndexes[4] = { 0 };
    int index = 0;

    for (int i = 1; i < 5; i++) {
        if (hand[i] == one) {
            matchingChars++;
        } else {
            notMatchingChars++;
            notMatchingCharsIndexes[index] = i;
            index++;
        }
    }

    // TODO - do I need to know how many don't match?
    if (matchingChars == 2 && notMatchingChars == 2) {
        return 1;
    } else if (notMatchingChars > 2) {
        char currentChar;
        int matches;
        for (int i = 0; i < 4; i++) {
            matches = 0;
            currentChar = hand[notMatchingCharsIndexes[i]];
            for (int j = 0; j < 4; j++) {
                if (i == j) continue;
                if (currentChar == hand[notMatchingCharsIndexes[j]]) {
                    matches++;
                }
            }

            if (matches == 2) {
                return 1;
            }
        }
    };

    return 0;
}

int getHandPairCount(const char hand[10]) {
    char currentChar;
    int matches, pairCount = 0;
    for (int i = 0; i < 5; i++) {
        matches = 0;
        currentChar = hand[i];
        for (int j = i + 1; j < 5; j++) {
            if (i == j) continue;
            if (currentChar == hand[j]) {
                matches++;
            }
        }

        if (matches == 1) {
            pairCount++;
        }
    }

    return pairCount;
}

int determineHandRank(char hand[10]) {

    enum HandRank rank = HIGH_CARD;

    if (isHandFiveOfAKind(hand) == 1) {
        rank = FIVE_OF_A_KIND;
        return rank;
    }

    if (isHandFourOfAKind(hand) == 1) {
        rank = FOUR_OF_A_KIND;
        return rank;
    }

    if (isHandFullHouse(hand) == 1) {
        rank = FULL_HOUSE;
        return rank;
    }

    if (isHandThreeOfAKind(hand) == 1) {
        rank = THREE_OF_A_KIND;
        return rank;
    }

    int pairCount = getHandPairCount(hand);
    if (pairCount == 2) {
        rank = TWO_PAIR;
        return rank;
    } else if(pairCount == 1) {
        rank = ONE_PAIR;
        return rank;
    }

    return rank;
}


int main() {

    char test[5] = "32T3T";
    printf("Pair count: %d\n", getHandPairCount(test));

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 7\\example.txt", "r");
    char line[20];
    int rows = 0;
    while(fgets(line, sizeof(line), fptr)) {
        rows++;
    }
    rewind(fptr);


    char hand[10] = "";
    int bet, handRank;
    char* token;

    // 7 is the number of possible hand "ranks" ( five of a kind, four of a kind, full house, three of a kind, two pair, one pair, high card )
    char** hands = calloc(7, rows * sizeof(char) * 6);
    int** betsOfRankedHands = calloc(7, rows * sizeof(int));

    for (int i = 0; i < 7; i++) {
        hands[i] = calloc(rows, sizeof(char) * 6);
        betsOfRankedHands[i] = calloc(rows, sizeof(int));
    }

    while(fgets(line, sizeof(line), fptr)) {
        token = strtok(line, " ");
        strcpy(hand, token);

        token = strtok(NULL, "\n");
        bet = atoi(token);

        handRank = determineHandRank(hand);

        for(int i = 0; i < rows; i++) {
            if (betsOfRankedHands[handRank][i] == 0) {
                betsOfRankedHands[handRank][i] = bet;
//                strcpy(hands[handRank][i], hand);
//                strcpy(&hands[handRank][i], hand);
                break;
            } else {

            }
        }

//        betsOfRankedHands[handRank][0];

//        printf("%s: %d\n", hand, bet);
    }
    fclose(fptr);


    for(int i = 0; i < 7; i++) {
        printf("Row %d: ", i + 1);
        for(int j = 0; j < rows; j++) {

        }
        printf("\n");
    }

    return 0;
}
