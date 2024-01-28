#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 8\\input.txt", "r");
    char line[300] = "";
    int rows = 0;

    fgets(line, sizeof(line), fptr); // Remove empty lne
    fgets(line, sizeof(line), fptr); // Remove empty lne
    while (fgets(line, sizeof(line), fptr)) {
        rows++;
    }
    rewind(fptr);

    char instructions[300] = "";
    char*** map = calloc(rows, 3 * sizeof(char) * 3);
    memset(line,0,strlen(line));
    fgets(instructions, sizeof(instructions), fptr); // Line of instructions
    fgets(line, sizeof(instructions), fptr); // Remove empty lne

    int index = 0;
    char* token;
    while (fgets(line, sizeof(line), fptr)) {
        map[index] = calloc(3, sizeof(char) * 3);

        token = strtok(line, " ");
        map[index][0] = calloc(3, sizeof(char));
        strcpy(map[index][0], token);

        token = strtok(NULL, "(");
        token = strtok(NULL, ",");
        map[index][1] = calloc(3, sizeof(char));
        strcpy(map[index][1], token);

        token = strtok(NULL, " )\n");
        map[index][2] = calloc(3, sizeof(char));
        strcpy(map[index][2], token);

        index++;
    }

    for (int i = 0; i < rows; i++) {
        if (map[i] == NULL) break;
        printf("%s %s %s\n", map[i][0], map[i][1], map[i][2]);
    }

    int steps = 0;
    char* currentNode; // Acts as index of map array
    char instruction;
    char** destinationElement;
    int instructionIndex = 0;

    for (int i = 0; i < rows; i++) {
        if (strcmp(map[i][0], "AAA") == 0) {
            currentNode = map[i][0];
        }
    }

    while (strcmp(currentNode, "ZZZ") != 0) {
        if (instructions[instructionIndex] == '\n') {
            instructionIndex = 0;
        }
        instruction = instructions[instructionIndex];
        for (int i = 0; i < rows; i++) {
            if (strcmp(map[i][0], currentNode) == 0) {
                destinationElement = map[i];
            }
        }

        if (instruction == 'L') {
            currentNode = destinationElement[1];
        } else if (instruction == 'R') {
            currentNode = destinationElement[2];
        }

        steps++;
        instructionIndex++;
    }

    printf("Final steps: %d", steps);
    return 0;
}
