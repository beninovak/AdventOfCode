#include <stdio.h>

int main() {

    /* Example input
    int times[3] = { 7, 15, 30 };
    int distances[3] = { 9, 40, 200 };
    */

    int times[4] = { 59, 79, 65, 75 };
    int distances[4] = { 597, 1234, 1032, 1328 };
    int waysToWin[4] = { 0 };

    // Speed -> millimeters/millisecond
    int speed, timeLeft;
    int numberOfWaysToWin = 0;

    for(int i = 0; i < 4; i++) {
        for (int buttonHoldTime = 1; buttonHoldTime < times[i]; buttonHoldTime++) {
            speed = buttonHoldTime;
            timeLeft = times[i] - buttonHoldTime;

            if (speed * timeLeft > distances[i]) {
                waysToWin[i]++;
            }
        }
    }

    int numberOfWaysToWinProduct = 1;

    for (int k = 0; k < 4; k++) {
        printf("Race %d ways to win: %d\n", k + 1, waysToWin[k]);
        numberOfWaysToWinProduct *= waysToWin[k];
    }

    printf("Number of ways to win: %d", numberOfWaysToWinProduct);
    return 0;
}
