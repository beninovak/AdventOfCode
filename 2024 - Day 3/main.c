#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    FILE* fptr = fopen("example.txt", "rb");

    char instruction_buffer[7];
    while(fread(instruction_buffer, sizeof(char), 7, fptr)) {

    }
    rewind(fptr);

    long total = 0;
    char buffer[4];
    while(fread(buffer, sizeof(char), 4, fptr)) {
        if (strcmp(buffer, "mul(") == 0) {
            char ch, last_ch;
            char num[3] = ""; // Numbers can be 1-3 digit as per the instructions.
            int consecutive_digits = 0;
            int looking_for_second = 0;
            ch = fgetc(fptr);
            if (ch < 48 || ch > 57) break;
            last_ch = ch;

            int num1 = 0, num2 = 0;

            while(1) {
                
                if (ch != 41 && ch != 44 && (ch < 48 || ch > 57)) break;

                if (ch >= 48 && ch <= 57) {
                    num[consecutive_digits] = ch;
                    consecutive_digits++;
                } else {
                    consecutive_digits = 0;
                }
                if (consecutive_digits > 3) {
                    break;
                }

                if (looking_for_second == 0 && last_ch >= 48 && last_ch <= 57 && ch == 44) { // 44 is ASCII comma (,)
                    num1 = atoi(num);
                    memset(num, '\0', 3);
                    looking_for_second = 1;
                }

                if (looking_for_second == 1 && last_ch >= 48 && last_ch <= 57 && ch == 41) { // 41 is ASCII closing bracket
                    num2 = atoi(num); 
                    memset(num, '\0', 3);
                    break;
                }
                
                last_ch = ch;
                ch = fgetc(fptr);
            }

            if (num1 > 0 && num2 > 0) {
                total += (num1*num2);
            }

        } else {
            if (!feof(fptr)) {
                fseek(fptr, -3, SEEK_CUR);
            } else {
                break;
            }
        }
    }

    printf("Total: %ld\n", total);

    free(fptr);
    return 0;
}
