#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2023 - Day 5\\example.txt", "r");
    long long seeds[30] = {0};

    long long
    seedMin = 0, seedMax = 0,
    soilMin = 0, soilMax = 0,
    fertilizerMin = 0, fertilizerMax = 0,
    waterMin = 0, waterMax = 0,
    lightMin = 0, lightMax = 0,
    temperatureMin = 0, temperatureMax = 0,
    humidityMin = 0, humidityMax = 0,
    locationMin = 0, locationMax = 0;

    char line[250] = "";
    char* token;
    fgets(line, sizeof(line), fptr);

    token = strtok(line, ": ");
    int count = 0;
    while(token != NULL) {
        token = strtok(NULL, " \n");
        seeds[count] = atoll(token);
        count++;
    }

    token = NULL;
    strcpy(line, "");

    long long destinationStart = 0, sourceStart = 0, range = 0;
    char stage[20] = "soil";
    while(fgets(line, sizeof(line), fptr)) {

        if (line[0] == '\n') {
            fgets(line, sizeof(line), fptr);

            token = strtok(line, "-");
            token = strtok(NULL, "-");
            token = strtok(NULL, " ");
            strcpy(stage, token);
            continue;
        }

        token = strtok(line, " ");
        destinationStart = atoll(token);

        token = strtok(NULL, " ");
        sourceStart = atoll(token);

        token = strtok(NULL, " \n");
        range = atoll(token);
//        strcpy(stage, token);

        if (strcmp(stage, "soil") == 0) {
            if (destinationStart < soilMin) {
                soilMin = destinationStart;
            }
        } else if (strcmp(stage, "soil") == 0) {

        } else if (strcmp(stage, "fertilizer") == 0) {

        } else if (strcmp(stage, "water") == 0) {

        } else if (strcmp(stage, "light") == 0) {

        } else if (strcmp(stage, "temperature") == 0) {

        } else if (strcmp(stage, "humidity") == 0) {

        } else if (strcmp(stage, "location") == 0) {

        }
    }

    fclose(fptr);

    return 0;
}
