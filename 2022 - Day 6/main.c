#include <stdio.h>
#include <string.h>

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 6\\input.txt", "r");
    char letter, lastFour[5] = "", message[15] = "";
    int counter = 1;
    int markerFound = 0, markerContainsDuplicate, messageContainsDuplicate;

    while ((letter = getc(fptr)) != EOF) {

        markerContainsDuplicate = 0;
        messageContainsDuplicate = 0;

        for (int i = 0; i < 4; i++) {
            lastFour[i] = lastFour[i + 1];
        }
        lastFour[3] = letter;

        for (int i = 0; i < 14; i++) {
            message[i] = message[i + 1];
        }
        message[13] = letter;

        for (int i = 0; i < 3; i++) {
            for (int j = 3; j > i; j--) {
                if (lastFour[i] == lastFour[j]) {
                    markerContainsDuplicate = 1;
                    break;
                }
            }
            if (markerContainsDuplicate == 1) break;
        }

        for (int i = 0; i < 13; i++) {
            for (int j = 13; j > i; j--) {
                if (message[i] == message[j]) {
                    messageContainsDuplicate = 1;
                    break;
                }
            }
            if (messageContainsDuplicate == 1) break;
        }

        if (markerFound == 0 && counter >= 4 && markerContainsDuplicate == 0) {
            printf("First marker is complete after: %d characters.\n", counter);
            printf("The marker is: %s\n", lastFour);
            markerFound = 1;
        }

        if (counter >= 14 && messageContainsDuplicate == 0) {
            printf("First message is complete after: %d characters.\n", counter);
            printf("The message is: %s\n", message);
            break;
        }

        counter++;
    }

    return 0;
}
