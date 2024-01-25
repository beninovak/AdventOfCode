#include <stdio.h>
#include <stdlib.h>

typedef struct _Vertex {
    int y;
    int x;
    int value;
    int distance;
    struct _Vertex* previous;
} Vertex;


void printArray(Vertex** nodes, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        if(nodes[i] == NULL) break;
        printf("y: %d, x: %d, value: %d, distance: %d\n", nodes[i]->y, nodes[i]->x, nodes[i]->value, nodes[i]->distance);
    }
}

void pushToArray(Vertex** visitedNodes, Vertex* node, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        if (visitedNodes[i] == NULL) {
            visitedNodes[i] = node;
            break;
        }
    }
}

void removeFromArray(Vertex** unvisitedNodes, Vertex* currentNode, int arraySize) {
    for(int i = 0; i < arraySize; i++) {
        if (unvisitedNodes[i] == NULL) continue;
        if (unvisitedNodes[i]->y == currentNode->y && unvisitedNodes[i]->x == currentNode->x) {
            unvisitedNodes[i] = NULL;
            break;
        }
    }
}

int isNodeVisited(Vertex** visitedNodes, Vertex* node, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        if(visitedNodes[i] == node) {
            return 1;
        }
    }
    return 0;
}

int allNodesVisited(Vertex** unVisitedNodes, int size) {
    for(int i = 0; i < size; i++) {
        if (unVisitedNodes[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

int isReachable(int current, int adjacent) {

    if (current == adjacent || current - adjacent == 1 || current - adjacent == -1) {
        return 1;
    }

    return 0;
}

int main() {
    setbuf(stdout, 0);
    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 12\\example.txt", "r");

    int columns = 0;
    while (getc(fptr) != '\n') {
        columns++;
    }
    rewind(fptr);

    int rows = 0;
    char line[200] = "";
    while (fgets(line, sizeof(line), fptr)) {
        rows++;
    }
    rewind(fptr);

    int arraySize = rows * columns;
    Vertex*** grid = calloc(rows, sizeof(Vertex*) * columns); // A 2D array of Vertex pointers
    Vertex** visitedNodes = calloc(arraySize, sizeof(Vertex*));
    Vertex** unVisitedNodes = calloc(arraySize, sizeof(Vertex*));

    int startX = 0, startY = 0, endX = 0, endY = 0;
    int row = 0, column = 0, count = 0;

    while (fgets(line, sizeof(line), fptr)) {

        grid[row] = calloc(columns, sizeof(Vertex*));
        column = 0;

        while (line[column] != '\n' && line[column] != '\0') {

            Vertex* currentNode = calloc(1, sizeof(Vertex));
            currentNode->y = row;
            currentNode->x = column;
            currentNode->distance = 1000000;
            currentNode->previous = NULL;
            currentNode->value = (int)line[column];

            if (line[column] == 'S') {
                startY = row;
                startX = column;
                currentNode->distance = 0;
                currentNode->value = (int)'a';
            } else if (line[column] == 'E') {
                endY = row;
                endX = column;
                currentNode->value = (int)'z';
            }

            grid[row][column] = currentNode;
            unVisitedNodes[count] = currentNode;
            column++;
            count++;
        }
        row++;
    }
    fclose(fptr);

    int y = 0, x = 0;
    int counter = 0;
    int pathLength = 0;
    int minDistance;
    int minDistanceIndex = (startY * columns) + startX;

    Vertex* currentNode = grid[startY][startX];
    Vertex* adjacentNode;

    while(currentNode != NULL) {

        y = currentNode->y;
        x = currentNode->x;

//        printf("\ny: %d, x: %d, distance: %d", adjacentNode->y, adjacentNode->x, adjacentNode->distance);

        if (y > 0 && isReachable(currentNode->value, grid[y - 1][x]->value)) {
            adjacentNode = grid[y - 1][x];
            if (isNodeVisited(visitedNodes, adjacentNode, arraySize) == 0 && currentNode->distance + 1 < grid[y - 1][x]->distance) {
                grid[y - 1][x]->distance = currentNode->distance + 1;
                grid[y - 1][x]->previous = currentNode;
            }
        }

        if (y < rows - 1 && isReachable(currentNode->value, grid[y + 1][x]->value)) {
            adjacentNode = grid[y + 1][x];
            if (isNodeVisited(visitedNodes, adjacentNode, arraySize) == 0 && currentNode->distance + 1 < grid[y + 1][x]->distance) {
                grid[y + 1][x]->distance = currentNode->distance + 1;
                grid[y + 1][x]->previous = currentNode;
            }
        }

        if (x > 0 && isReachable(currentNode->value, grid[y][x - 1]->value)) {
            adjacentNode = grid[y][x - 1];
            if (isNodeVisited(visitedNodes, adjacentNode, arraySize) == 0 && currentNode->distance + 1 < grid[y][x - 1]->distance) {
                grid[y][x - 1]->distance = currentNode->distance + 1;
                grid[y][x - 1]->previous = currentNode;
            }
        }

        if (x < columns - 1 && isReachable(currentNode->value, grid[y][x + 1]->value)) {
            adjacentNode = grid[y][x + 1];
            if (isNodeVisited(visitedNodes, adjacentNode, arraySize) == 0 && currentNode->distance + 1 < grid[y][x + 1]->distance) {
                grid[y][x + 1]->distance = currentNode->distance + 1;
                grid[y][x + 1]->previous = currentNode;
            }
        }
        
        pushToArray(visitedNodes, currentNode, arraySize);
        removeFromArray(unVisitedNodes, currentNode, arraySize);

//        printf("\n----------------Step %d, Visited nodes---------------\n", counter + 1);
//        printArray(visitedNodes, arraySize);
//        printf("\n-------------------------END-------------------------\n");

        counter++;

        minDistance = 1000000;
        for (int i = 0; i < arraySize; i++) {
            if (unVisitedNodes[i] == NULL) continue;

            if (unVisitedNodes[i]->distance < minDistance) {
                minDistance = unVisitedNodes[i]->distance;
                minDistanceIndex = i;
            }
        }
        currentNode = unVisitedNodes[minDistanceIndex];
    }

    pathLength = grid[endY][endX]->distance;
    char* path = calloc(pathLength + 1, sizeof(char));

    path[pathLength] = '\0';

    int index = 0;
    Vertex* previousNode = grid[endY][endX];

    while(previousNode != NULL) {
        path[pathLength - index] = (char)previousNode->value;
        previousNode = previousNode->previous;
        index++;
    }

    printf("\nPath: %s\n", path);
    printf("\nPath length: %d\n", pathLength);

    printf("\n\n");

    return 0;
}