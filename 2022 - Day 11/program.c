#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

enum OPERATION {
    ADD,
    MULTIPLY
};

struct Monkey {
    int testDivisibleBy;
    int testTrueMonkeyId;
    int testFalseMonkeyId;
    enum OPERATION operation;
    int operationValue;
    int inspectedItems;
    long long items[50];
};

void swap(long* xp, long* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Selection sort
void sortArrayDesc(long arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
        // Find the maximum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] > arr[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

int main() {

    long long worryLevel;

    // Starting monkey values. If operationValue is 0, that means the old worryLevel should be multiplied by itself.
    struct Monkey Monkey0 = { 3, 7, 4, MULTIPLY, 5, 0, { 66, 71, 94 } };
    struct Monkey Monkey1 = { 17, 3, 0, ADD, 6, 0, { 70 } };
    struct Monkey Monkey2 = { 2, 3, 1, ADD, 5, 0, { 62, 68, 56, 65, 94, 78 } };
    struct Monkey Monkey3 = { 19, 7, 0, ADD, 2, 0, { 89, 94, 94, 67 } };
    struct Monkey Monkey4 = { 11, 5, 6, MULTIPLY, 7, 0, { 71, 61, 73, 65, 98, 98, 63 } };
    struct Monkey Monkey5 = { 5, 2, 1, ADD, 7, 0, { 55, 62, 68, 61, 60 } };
    struct Monkey Monkey6 = { 13, 5, 2, ADD, 1, 0, { 93, 91, 69, 64, 72, 89, 50, 71 } };
    struct Monkey Monkey7 = { 7, 4, 6, MULTIPLY, 0, 0, { 76, 50 } };

    int monkeyCount = 8;
    struct Monkey monkeys[8] = { Monkey0, Monkey1, Monkey2, Monkey3, Monkey4, Monkey5, Monkey6, Monkey7 };
    long monkeyInspections[8];

    long LCM = 1;

    for (int h = 0; h < monkeyCount; h++) {
        LCM *= monkeys[h].testDivisibleBy;
    }

    printf("LCM: %ld\n", LCM);

    // 20 Rounds
    for (int i = 0; i < 3776; i++) {

        for (int j = 0; j < monkeyCount; j++) {

            int monkeyItemCount = sizeof(monkeys[j].items) / sizeof(monkeys[j].items[0]);

            for (int k = 0; k < monkeyItemCount; k++) {

                if (monkeys[j].items[k] == 0) {
                    continue;
                }

                monkeys[j].inspectedItems++;
                worryLevel = monkeys[j].items[k];

                // Worry level changes as monkey inspects item
                switch (monkeys[j].operation) {

                    case ADD:
                        worryLevel += monkeys[j].operationValue;
                        break;

                    case MULTIPLY:

                        if (monkeys[j].operationValue == 0) {
                            worryLevel *= worryLevel;
                        } else {
                            worryLevel *= monkeys[j].operationValue;
                        }
                        break;
                }

//                worryLevel = (int)floorf((float)worryLevel / 3);
                printf("Worry before: %lld\n", worryLevel);
                worryLevel = worryLevel % LCM;
                printf("Worry after: %lld\n", worryLevel);

                // Monkey tests worry level
                int monkeyToThrowToId;

                if (worryLevel % monkeys[j].testDivisibleBy == 0) {
                    monkeyToThrowToId = monkeys[j].testTrueMonkeyId;
                } else {
                    monkeyToThrowToId = monkeys[j].testFalseMonkeyId;
                }

                // Give item to appropriate monkey
                int arrSize = sizeof(monkeys[monkeyToThrowToId].items) / sizeof(monkeys[monkeyToThrowToId].items[0]);
                int length = 0;

                for (int m = 0; m < arrSize; m++) {
                    if (monkeys[monkeyToThrowToId].items[m] != 0) {
                        length++;
                    }
                }

                monkeys[monkeyToThrowToId].items[length] = worryLevel;

                // Remove item from current monkey's list
                monkeys[j].items[k] = 0;
            }
        }

//        if ((i + 1) % 5 == 0) {
            printf("\nResults after round %d:\n", (i + 1));

            for (int n = 0; n < monkeyCount; n++) {

                long long *finalItems = monkeys[n].items;
                printf("Monkey %d final items: ", n);

                for (int q = 0; q < 10; q++) {
                    printf("%lld ", finalItems[q]);
                }

                printf("\n");
            }
            printf("\n-------------------------------------------\n");
//        }
    }
    // ------------ Rounds finished ----------------

    for (int n = 0; n < monkeyCount; n++) {
        monkeyInspections[n] = monkeys[n].inspectedItems;
        printf("Monkey %d inspected %ld items \n", n, monkeyInspections[n]);
    }

    sortArrayDesc(monkeyInspections, monkeyCount);

    for (int o = 0; o < monkeyCount; o++) {
        printf("%ld ", monkeyInspections[o]);
    }

    printf("\n1st place Monkey: %ld: --- 2nd place Monkey: %ld\n", monkeyInspections[0], monkeyInspections[1]);
    long n     monkeyBusiness = monkeyInspections[0] * monkeyInspections[1];

    printf("\nMonkey business: %lld\n", monkeyBusiness);

    return 0;
}