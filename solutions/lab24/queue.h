#pragma once
#include "lexeme.h"
#include <stdbool.h>
#include <stdlib.h>

#define QUEUE_RESIZE_STEP 10

typedef Lexeme* QUEUE_T;

typedef struct {
    int length;
    int start;
    int depth;
    QUEUE_T *data;
} Queue;

Queue* newQueue (int length);
void deleteQueue (Queue *queue, void (*deleteItem)(QUEUE_T item));
bool isEmptyQueue (Queue *queue);
QUEUE_T topQueue (Queue *queue);
void pushQueue (Queue *queue, QUEUE_T elem);
void popQueue (Queue *queue, void (*deleteItem)(QUEUE_T item));
void resizeQueue (Queue *queue, int dlen);

void printQueue (Queue *queue, void (*deleteItem)(QUEUE_T item), QUEUE_T (*copyElem)(QUEUE_T elem), void (*elemPrinter)(QUEUE_T elem));