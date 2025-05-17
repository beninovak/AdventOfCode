#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    FILE* fptr = fopen("input.txt", "rb");
    if (fptr == NULL) {
        printf("Cannot open file!\n");
        return 1;
    }
    
    char line[64] = "";
    char* token;
    int previous = 0, current = 0;
    int safe_reports = 0;
    int direction = 0; // -1 if decreasing, 1 if increasing
    int count;
    int unsafe;

    while(fgets(line, sizeof(line), fptr)) {

        printf("\n");
        count = 0;
        unsafe = 0;
        token = strtok(line, " \n");
        while(token != NULL) {
            current = atoi(token);
            printf("%d ", current);

            if (count == 0) {
                previous = current;
                token = strtok(NULL, " \n");
                count++;
                continue;
            }

            int diff = current - previous;
            if (diff < 0) {
                diff = diff * -1;
            }
            if (diff < 1 || diff > 3) {
                printf(" - Big diff");
                unsafe = 1;
                break; 
            }

            if (count > 1) {
                if ((direction == -1 && current > previous) || 
                    (direction == 1 && current < previous)
                ) {
                    printf(" - Wrong direction");
                    unsafe = 1;
                    break;
                }

            }

            if (current < previous) {
                direction = -1;
            } else {
                direction = 1;
            }

                         
            previous = current;
            token = strtok(NULL, " \n");
            count++;
        }
        if (unsafe == 0) {
            safe_reports++;
        }
    }

    printf("\nSafe reports: %d\n", safe_reports);
    return 0;
}
