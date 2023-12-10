#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Vertex {
    int x;
    int y;
    int value;
    int distance;
    int visited;
    struct Vertex* prev;
} Vertex;

typedef struct VertexList {
    Vertex* first;
    Vertex* last;
} VertexList;

void arrayShiftLeft(Vertex array[], int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
        array[i] = array[i + 1];
        if (array[i + 1].value == 0) {
            return;
        }
    }
}

void handleVertex (Vertex** vertices, int x, int y, Vertex currentVertex) {
    vertices[y][x].prev = &currentVertex;
    vertices[y][x].visited = 1;
    if (currentVertex.distance + 1 < vertices[y][x].distance) {
        vertices[y][x].distance = currentVertex.distance + 1;
    }
}

//void arrayShiftRight(Vertex* array[]) {
//    int index = 0;
//    while (array[index]->value != 0) {
//        array[index] = array[index - 1];
//        index++;
//    }
//}

int main() {

    FILE* fptr = fopen("C:\\Users\\Janez Povezava\\CLionProjects\\AdventOfCode\\2022 - Day 12\\input.txt", "r");
    int ch = getc(fptr);
    int chs = 0;
    int rows = 0;
    int lineLength = 0;
    int startX, startY, endX, endY;

    while (ch != '\n') {
        lineLength++;
        ch = getc(fptr);
    }

    rewind(fptr);

    char* line = calloc(1, sizeof(char) * (lineLength + 1));
    while (fgets(line, sizeof(char) * (lineLength + 2), fptr)) {
        rows++;
    }

    rewind(fptr);

    Vertex** vertices = calloc(rows, sizeof(Vertex) * lineLength);
    vertices[0] = calloc(lineLength, sizeof(Vertex));

    ch = getc(fptr);
    rows = 0;

    while (ch != EOF) {
        if (ch == '\n') {
            rows++;
            ch = getc(fptr);
            vertices[rows] = calloc(lineLength, sizeof(Vertex));
            continue;
        } else if (ch == 'S') {
            startX = chs - (rows * lineLength);
            startY = rows;
        } else if (ch == 'E') {
            endX = chs - (rows * lineLength);
            endY = rows;
        }

        Vertex newVertex = {
            .x = chs - (rows * lineLength),
            .y = rows,
            .value = ch,
            .distance = INT_MAX,
            .visited = 0,
            .prev = NULL,
        };

        vertices[rows][chs - (rows * lineLength)] = newVertex;

        chs++;
        ch = getc(fptr);
    }
    fclose(fptr);

    Vertex currentVertex = vertices[startY][startX];
    currentVertex.distance = 0;
    Vertex queue[rows * lineLength];
    queue[0] = currentVertex;
    int x = currentVertex.x;
    int y = currentVertex.y;

    while (queue[0].value != 0) {

        currentVertex = queue[0];
        x = currentVertex.x;
        y = currentVertex.y;

        // Dequeue
        arrayShiftLeft(queue, rows * lineLength);

        // Check left
        if (x > 0) {
            if (vertices[y][x - 1].visited == 0) {
                handleVertex(vertices, x - 1, y, currentVertex);
            }
        }
        // Check right
        if (x < lineLength) {
            if (vertices[y][x + 1].visited == 0) {
                handleVertex(vertices, x + 1, y, currentVertex);
            }
        }
        // Check top
        if (y > 0) {
            if (vertices[y - 1][x].visited == 0) {
                handleVertex(vertices, x, y - 1, currentVertex);
            }
        }
        // Check bottom
        if (y < rows) {
            if (vertices[y + 1][x].visited == 0) {
                handleVertex(vertices, x, y + 1, currentVertex);
            }
        }
    }

    Vertex endVertex = vertices[endY][endX];
    Vertex temp = endVertex;

    int count = 0;
    while (temp.prev != NULL) {
        temp = *temp.prev;
        count++;
    }

    printf("Vertex [5][72] value: %d\n", vertices[5][72].value);
    printf("Vertex [5][72] distance: %d\n", vertices[5][72].distance);
    printf("Vertex [5][72] visited: %d\n", vertices[5][72].visited);
    printf("Vertex [5][72] previous: %p\n", vertices[5][72].prev);
    printf("Steps required to get from start to finish: %d", count);

    return 0;
}