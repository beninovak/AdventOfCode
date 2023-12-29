#include <stdio.h>
#include <stdlib.h>

void printArray(int** nodes) {

    int index = 0;

    while(1) {
        if(nodes[index] == NULL) break;

        printf("y: %d, x: %d\n", nodes[index][0], nodes[index][1]);

        index++;
    }
}

void arrayPopLast(int** array) {
    int index = 0;
    while(1) {
        if (array[index + 1] == NULL) {
            array[index] = NULL;
            break;
        }
        index++;
    }
}

void arrayPopFirst(int** array) {
    array[0] = NULL;
    int index = 0;
    while(1) {
        array[index] = array[index + 1];
        array[index + 1] = NULL;

        if (array[index + 1] == NULL) {
            break;
        }
        index++;
    }
}


void pushToArray(int** nodes, const int* node) {

    int count = 0;
//    printf("\n");
    while(1) {
        if (nodes[count] == NULL) {
            nodes[count] = calloc(2, sizeof(int));
            nodes[count][0] = node[0];
            nodes[count][1] = node[1];
//            printArray(nodes);
            break;
        }

        count++;
    }
//    printf("\n");
}

int arrayContains(int** visitedNodes, const int node[2]) {

    int count = 0;
    while(visitedNodes[count] != NULL) {
        if (visitedNodes[count][0] == node[0] && visitedNodes[count][1] == node[1]) {
            return 1;
        }
        count++;
    }

    return 0;
}

int isReachable(char current, char adjacent) {

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


    char** grid = calloc(rows, sizeof(char) * columns);
    int startX, startY, endX, endY;

    int row = 0, column = 0;
    while (fgets(line, sizeof(line), fptr)) {

        grid[row] = calloc(columns, sizeof(char));
        column = 0;

        while (line[column] != '\0') {
            grid[row][column] = line[column];

            if (line[column] == 'S') {
                startY = row;
                startX = column;
                grid[row][column] = 'a';
            } else if (line[column] == 'E') {
                endY = row;
                endX = column;
                grid[row][column] = 'z';
            }

            column++;
        }
        row++;
    }
    fclose(fptr);

    int x = startX, y = startY;
    int** queue = calloc(rows * columns, sizeof(int) * 2);
    int queueSize = rows * columns;
    int** visitedNodes = calloc(rows * columns, sizeof(int) * 2);
    int* currentNode= calloc(2, sizeof(int));
    int* previousNode = calloc(2, sizeof(int));
    int* adjacentNode = calloc(2, sizeof(int));
    int pathLength = 0;
    int anyAdjacent = 0;

    currentNode[0] = startY;
    currentNode[1] = startX;
    previousNode[0] = startY;
    previousNode[1] = startX;

    queue[0] = currentNode;

    int index = 0;
    int counter = 0;
    while(queue[index] != NULL/*counter < 10*/) {

        y = queue[index][0];
        x = queue[index][1];

        if (counter == 0) {
            arrayPopFirst(queue);
        } else {
            arrayPopLast(queue);
        }

        if (y == endY && x == endX) {
//            pathLength++;
            break;
        }

        currentNode[0] = y;
        currentNode[1] = x;

        if (arrayContains(visitedNodes, currentNode) == 1) {
            arrayPopLast(queue);
            counter++;
            continue;
        }

        anyAdjacent = 0;
        if (y > 0 && isReachable(grid[y][x], grid[y - 1][x])) {
            adjacentNode[0] = y - 1;
            adjacentNode[1] = x;

            if (y - 1 == endY && x == endX) break;

            if (arrayContains(visitedNodes, adjacentNode) == 0 && arrayContains(queue, adjacentNode) == 0) {
                anyAdjacent = 1;
                pushToArray(queue, adjacentNode);
            }
        }

        if (y < rows - 1 && isReachable(grid[y][x], grid[y + 1][x])) {
            adjacentNode[0] = y + 1;
            adjacentNode[1] = x;

            if (y + 1 == endY && x == endX) break;

            if (arrayContains(visitedNodes, adjacentNode) == 0 && arrayContains(queue, adjacentNode) == 0) {
                anyAdjacent = 1;
                pushToArray(queue, adjacentNode);
            }
        }

        if (x > 0 && isReachable(grid[y][x], grid[y][x - 1])) {
            adjacentNode[0] = y;
            adjacentNode[1] = x - 1;

            if (y == endY && x - 1 == endX) break;

            if (arrayContains(visitedNodes, adjacentNode) == 0 && arrayContains(queue, adjacentNode) == 0) {
                anyAdjacent = 1;
                pushToArray(queue, adjacentNode);
            }
        }

        if (x < columns - 1 && isReachable(grid[y][x], grid[y][x + 1])) {
            adjacentNode[0] = y;
            adjacentNode[1] = x + 1;

            if (y == endY && x + 1 == endX) break;

            if (arrayContains(visitedNodes, adjacentNode) == 0 && arrayContains(queue, adjacentNode) == 0) {
                anyAdjacent = 1;
                pushToArray(queue, adjacentNode);
            }
        }

        if (anyAdjacent == 1) {
            pathLength++;
        }

        if (anyAdjacent == 0) {
            pathLength--;
        }

        pushToArray(visitedNodes, currentNode);

//        printf("\n----------------%d---------------\n", counter + 1);
//        printArray(visitedNodes);
//
//        printf("---------------Queue:--------------\n");
//        printArray(queue);
//        printf("Path length: %d", pathLength);
//        printf("\n---------------END---------------\n");

        index = 0;
        for (int k = 0; k < queueSize; k++) {
            if (queue[k] != NULL) {
                index++;
            } else {
                break;
            }
        }

        index--;

        counter++;
//        printf("%d\n", counter + 1);
    }

//    for (int i = 0; i < rows; i++) {
//        for(int j = 0; j < columns; j++) {
//            printf("%c ", grid[i][j]);
//        }
//        printf("\n");
//    }

    printf("Path length: %d", pathLength);

    return 0;
}