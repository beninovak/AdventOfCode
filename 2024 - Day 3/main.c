#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
    FILE* fptr = fopen("input.txt", "rb");

    char  do_buffer[5] = "";
    char  dont_buffer[8] = "";
    int   instruction_count = 64;
    long* do_instructions = calloc(instruction_count, sizeof(long));
    long* dont_instructions = calloc(instruction_count, sizeof(long));
    int   total_instructions = 0;

    while(fread(do_buffer, sizeof(char), 4, fptr)) {
        if(strcmp(do_buffer, "do()") == 0) {
            do_instructions[total_instructions] = ftell(fptr) - 4; // ftell() - 4 to account for fread() having moved the pointer.
            total_instructions++;
            if (total_instructions == instruction_count) {
                instruction_count *= 2;
                do_instructions = realloc(do_instructions, instruction_count);
            }
        } else {
            if (!feof(fptr)) {
                fseek(fptr, -3, SEEK_CUR);
            } else {
                break;
            }
        }
    }

    rewind(fptr);
    instruction_count = 64;
    total_instructions = 0;
    while(fread(dont_buffer, sizeof(char), 7, fptr)) {
        if(strcmp(dont_buffer, "don't()") == 0) {
            dont_instructions[total_instructions] = ftell(fptr) - 7;  // ftell() - 7 to account for fread() having moved the pointer.
            total_instructions++;
            if (total_instructions == instruction_count) {
                instruction_count *= 2;
                dont_instructions = realloc(dont_instructions, instruction_count);
            }
        } else {
            if (!feof(fptr)) {
                fseek(fptr, -6, SEEK_CUR);
            } else {
                break;
            }
        }
    }
    rewind(fptr);
    fseek(fptr, 0, SEEK_SET);

    printf("\nDo: ");
    for(int i = 0; i < instruction_count;i++) {
        printf("%ld ", do_instructions[i]);
    }

    printf("\nDon't: ");
    for(int i = 0; i < instruction_count;i++) {
        printf("%ld ", dont_instructions[i]);
    }
    
    long total = 0;
    char buffer[5] = "";
    int current_position;
    int closest_do, closest_dont;
    while(fread(buffer, sizeof(char), 4, fptr)) {
        if (strcmp(buffer, "mul(") == 0) {
            closest_do = closest_dont = 0;
            current_position = ftell(fptr) - 4;
                
            for (int i = 0; i < instruction_count; i++) {
                if (do_instructions[i] == 0 || do_instructions[i] > current_position) break;
                closest_do = do_instructions[i];
            }

            for (int i = 0; i < instruction_count; i++) {
                if (dont_instructions[i] == 0 || dont_instructions[i] > current_position) break;
                closest_dont = dont_instructions[i];
            }
            if (closest_dont > closest_do) continue;

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

    printf("\nTotal: %ld\n", total);
    free(do_instructions);
    free(dont_instructions);
    fclose(fptr);
    return 0;
}
