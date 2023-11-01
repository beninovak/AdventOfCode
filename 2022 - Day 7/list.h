#pragma once
#include <stdlib.h>

typedef struct _listNode {
    void* value;
    struct _listNode* next;
} listNode;

typedef struct _list {
    listNode* first;
    listNode* last;
} list;

void addToList(list* list, void* value) {

    listNode* node = calloc(1, sizeof(listNode));
    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
}

void* valueAtIndex(list* list, int index) {

    int count = 0;
    listNode* lastNode = list->first;

    while (1) {
        if (count == index) {
            return lastNode->value;
        }

        lastNode = lastNode->next;
        count++;
    }
}

void forEach(list* list, void(*func)(void*)) {

    listNode* lastNode = list->first;

    while (lastNode != NULL) {

        func(lastNode->value);
        lastNode = lastNode->next;
    }
}