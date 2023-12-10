#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 2\\input.txt", "r");
    char line[200];
    int id, gameIds = 0, colorCount;
    char* token;
    char color[10] = "", colorToken[10] = "";

    int redInBag = 12, greenInBag = 13, blueInBag = 14;

    int red, green, blue, setOver = 0, setPossible = 1;

    while (fgets(line, sizeof(line), fptr)) {

        red = green = blue = 0;
        token = strtok(line, " ");
        token = strtok(NULL, ":");
        id = atoi(token);

        setPossible = 1;
        token = strtok(NULL, " ");

        while (token != NULL) {
            colorCount = atoi(token);

            token = strtok(NULL, ",\n ");
            strcpy(colorToken, token);

            for (int i = 0; i < strlen(colorToken) + 1; i++) {
                if (colorToken[i] == ';' || colorToken[i] == '\0') {
                    setOver = 1;
                    break;
                } else {
                    color[i] = colorToken[i];
                }
            }

            if (strcmp(color, "red") == 0) {
                red += colorCount;
            } else if (strcmp(color, "green") == 0) {
                green += colorCount;
            } else if (strcmp(color, "blue") == 0) {
                blue += colorCount;
            }

            memset(color, 0, sizeof(color));

            if (setOver) {
                if (red > redInBag || green > greenInBag || blue > blueInBag) {
                    setPossible = 0;
                    break;
                }
                red = green = blue = setOver = 0;
            }

            token = strtok(NULL, " ");
        }

        if (setPossible) {
            gameIds += id;
        }
    }

    printf("Sum of possible games: %d", gameIds);

    fclose(fptr);
    return 0;
}