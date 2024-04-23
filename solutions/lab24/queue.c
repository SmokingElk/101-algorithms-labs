#include "queue.h"

#include <stdio.h>

Queue* newQueue (int length) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->length = length;
    queue->data = NULL;
    if (length > 0) queue->data = (QUEUE_T*)malloc(sizeof(QUEUE_T) * length);
    queue->start = 0;
    queue->depth = 0;
    
    return queue;
}

void deleteQueue (Queue *queue, void (*deleteItem)(QUEUE_T item)) {
    while (!isEmptyQueue(queue)) popQueue(queue, deleteItem);
    if (queue->data != NULL) free(queue->data);
    free(queue);
}

bool isEmptyQueue (Queue *queue) { return queue->depth == 0; }
QUEUE_T topQueue (Queue *queue) { return queue->data[queue->start]; }

void pushQueue (Queue *queue, QUEUE_T elem) {
    if (queue->depth == queue->length) resizeQueue(queue, QUEUE_RESIZE_STEP);
    queue->data[(queue->start + queue->depth) % queue->length] = elem;
    queue->depth++;
}

void popQueue (Queue *queue, void (*deleteItem)(QUEUE_T item)) {
    deleteItem(queue->data[queue->start]);
    queue->depth--;
    queue->start = (queue->start + 1) % queue->length;
}

void resizeQueue (Queue *queue, int dlen) {
    QUEUE_T *newArray = (QUEUE_T *)malloc(sizeof(QUEUE_T) * (queue->length + dlen));
    for (int i = 0; i < queue->length; i++) newArray[i] = queue->data[i];

    if (queue->data != NULL) free(queue->data);
    queue->data = newArray;
    queue->length += dlen;
}

void printQueue (Queue *queue, void (*deleteItem)(QUEUE_T item), QUEUE_T (*copyElem)(QUEUE_T elem), void (*elemPrinter)(QUEUE_T elem)) {
    Queue *queueTmp = newQueue(0);

    while (!isEmptyQueue(queue)) {
        elemPrinter(topQueue(queue));
        pushQueue(queueTmp, copyElem(topQueue(queue)));
        popQueue(queue, deleteItem);
    }
    
    while (!isEmptyQueue(queueTmp)) {
        pushQueue(queue, copyElem(topQueue(queueTmp)));
        popQueue(queueTmp, deleteItem);
    } 

    deleteQueue(queueTmp, deleteItem);
}