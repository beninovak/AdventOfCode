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
    int items[50];
};

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Selection sort
void sortArrayDesc(int arr[], int n)
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

    int worryLevel;

    // Starting monkey values. If operationValue is 0, that means the old worryLevel should be multiplied by itself.
    struct Monkey Monkey0 = { 23, 2, 3, MULTIPLY, 19, 0, { 79, 98 } };
    struct Monkey Monkey1 = { 19, 2, 0, ADD, 6, 0, { 54, 65, 75, 74 } };
    struct Monkey Monkey2 = { 13, 1, 3, MULTIPLY, 0, 0, { 79, 60, 97 } };
    struct Monkey Monkey3 = { 17, 0, 1, ADD, 3, 0, { 74 } };

    int monkeyCount = 4;
    struct Monkey monkeys[4] = { Monkey0, Monkey1, Monkey2, Monkey3 };
    int monkeyInspections[4];

    // 20 Rounds
    for (int i = 0; i < 20; i++) {

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

                worryLevel = (int)floorf((float)worryLevel / 3);

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


        printf("\nResults after round %d:\n", (i + 1));

        for (int n = 0; n < monkeyCount; n++) {

            int *finalItems = monkeys[n].items;
            printf("Monkey %d final items: ", n);

            for (int q = 0; q < 10; q++) {
                printf("%d ", finalItems[q]);
            }

            printf("\n");
        }
        printf("\n-------------------------------------------\n");
    }
    // ------------ Rounds finished ----------------

    for (int n = 0; n < monkeyCount; n++) {
        monkeyInspections[n] = monkeys[n].inspectedItems;
        printf("Monkey %d inspected %d items: \n", n, monkeyInspections[n]);
    }

    sortArrayDesc(monkeyInspections, monkeyCount);

    for (int o = 0; o < monkeyCount; o++) {
        printf("%d ", monkeyInspections[o]);
    }

    int monkeyBusiness = monkeyInspections[0] * monkeyInspections[1];

    printf("Monkey business: %d\n", monkeyBusiness);

    return 0;
}