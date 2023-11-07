#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

typedef struct _file {
    long long size;
    char* name;
} file;

typedef struct _directory {
    char* name;
    list *files;
    list *childDirs;
    long long size;
    struct _directory *parentDirectory;
} directory;

void printDirectory(void* value) {
    directory* dir = (directory*)value;
    printf("%s: \n", dir->name);
}

long long getFileSize(directory* value) {

    long long totalFileSize = 0;
    directory* dir = value;

    listNode* lastNode = dir->files->first;

    while (lastNode != NULL) {
        totalFileSize += ((file*)lastNode->value)->size;
        lastNode = lastNode->next;
    }

    lastNode = dir->childDirs->first;
    while (lastNode != NULL) {
        totalFileSize += getFileSize(lastNode->value);
        lastNode = lastNode->next;
    }

    dir->size = totalFileSize;

    return totalFileSize;
}

int main() {

    FILE *fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 7\\input.txt", "r");
    char *token;
    char line[30];
    char* lastCommand;
    char* argument;
    list *directories = calloc(1, sizeof(list));

    directory* currentDirectory = NULL;

    while (fgets(line, sizeof(line), fptr)) {

        token = strtok(line, " ");

        if (strcmp(token, "$") == 0) {
            token = strtok(NULL, " \n");
            lastCommand = token;

            if (strcmp(lastCommand, "cd") == 0) {
                token = strtok(NULL, " \n");
                argument = token;

                if (strcmp(argument, "/") == 0) {
                    currentDirectory = calloc(1, sizeof(directory));
                    currentDirectory->name = "/";
                    currentDirectory->files = calloc(1, sizeof(list)),
                    currentDirectory->childDirs = calloc(1, sizeof(list)),
                    currentDirectory->parentDirectory = NULL;
                    addToList(directories, currentDirectory);
                    continue;
                }

                if (strcmp(argument, "..") == 0) {
                    currentDirectory = currentDirectory->parentDirectory;
                    continue;
                }

                listNode* lastNode = currentDirectory->childDirs->first;

                while (1) {
                    if (strcmp(((directory*)lastNode->value)->name, argument) == 0) {
                        currentDirectory = (directory*)lastNode->value;
                        break;
                    }
                    lastNode = lastNode->next;
                }
            }
        }

        if (strcmp(token, "dir") == 0) {
            token = strtok(NULL, " \n");
            directory *newDir = calloc(1, sizeof(directory));
            newDir->name = calloc(strlen(token) + 1, sizeof(char));
            strcpy(newDir->name, token);
            newDir->files = calloc(1, sizeof(list)),
            newDir->childDirs = calloc(1, sizeof(list));
            newDir->parentDirectory = currentDirectory;
            addToList(currentDirectory->childDirs, newDir);
            addToList(directories, newDir);
        } else {
            file* newFile = calloc(1, sizeof(file));
            newFile->size = atoll(token);
            token = strtok(NULL, " \n");
            newFile->name = token;
            addToList(currentDirectory->files, newFile);
        }
    }

    fflush(stdout);
    getFileSize(directories->first->value);

    long long dirFileSize = 0;
    listNode* lastNode = directories->first;
    while (lastNode != NULL) {

        long long size = ((directory*)lastNode->value)->size;
        if (size <= 100000) {
            dirFileSize += size;
        }
        lastNode = lastNode->next;
    }

    long long maxSize = 70000000;
    long long requiredSize = 30000000;
    long long usedSize = ((directory*)directories->first->value)->size;
    long long availableSize = maxSize - usedSize;
    long long neededSize = requiredSize - availableSize;

    long long previousMinSize = maxSize;

    lastNode = directories->first;
    while (lastNode != NULL) {

        long long size = ((directory*)lastNode->value)->size;
        if (size < previousMinSize && size >= neededSize) {
            previousMinSize = size;
        }
        lastNode = lastNode->next;
    }

    printf("Root file size, ja: %lld\n", usedSize);
    printf("Available file size, ja: %lld\n", availableSize);
    printf("Needed file size, ja: %lld\n", previousMinSize);

    return 0;
}
