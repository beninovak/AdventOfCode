#include <stdio.h>

int main() {

    /* Example input
    int times[3] = { 7, 15, 30 };
    int distances[3] = { 9, 40, 200 };
    */

    long long time = 59796575;
    long long distance = 597123410321328;

//    int time = 71530;
//    long long distance = 940200;

    long long waysToWin = 0;

    // Speed -> millimeters/millisecond
    long long speed, timeLeft;

    for (long long buttonHoldTime = 1; buttonHoldTime < time; buttonHoldTime++) {
        speed = buttonHoldTime;
        timeLeft = time - buttonHoldTime;

        if (speed * timeLeft > distance) {
            waysToWin++;
        }
    }

//    int numberOfWaysToWinProduct = 1;

//    for (int k = 0; k < 4; k++) {
//        printf("Race %d ways to win: %d\n", k + 1, waysToWin[k]);
//        numberOfWaysToWinProduct *= waysToWin[k];
//    }

    printf("Number of ways to win: %lld", waysToWin);
    return 0;
}
