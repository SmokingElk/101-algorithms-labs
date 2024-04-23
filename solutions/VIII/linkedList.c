#include "linkedList.h"

ListNode createNode (ListElem value) {
    ListNode res = (ListNode)malloc(sizeof(_ListNode));
    res->value = value;
    res->next = NULL;
    res->prev = NULL;
    return res;
}

void deleteNode (ListNode node) {
    free(node);
}

ListIter createIter (ListNode node) {
    ListIter res = {node};
    return res;
}

ListIter iterNext (ListIter iter) {
    iter.node = iter.node->next;
    return iter;
}

ListIter iterPrev (ListIter iter) {
    iter.node = iter.node->prev;
    return iter;
}

bool iterEquals (ListIter iter1, ListIter iter2) {
    return iter1.node == iter2.node;
}

bool iterNotEquals (ListIter iter1, ListIter iter2) {
    return iter1.node != iter2.node;
}

ListElem iterFetch (ListIter iter) {
    return iter.node->value;
}

void iterStore (ListIter iter, ListElem value) {
    iter.node->value = value;
}

List createList () {
    List res = (List)malloc(sizeof(_List));
    ListNode term = createNode(0);
    term->next = term;
    term->prev = term;
    res->begin = createIter(term);
    res->end = createIter(term);
    return res;
}

void deleteList (List list) {
    ListIter it = listBegin(list);

    while (iterNotEquals(it, listEnd(list))) {
        ListNode ptn = it.node;
        it = iterNext(it);
        deleteNode(ptn);
    }
    
    deleteNode(it.node);
    free(list);
}

ListIter listBegin (List list) {
    return list->begin;
}

ListIter listEnd (List list) {
    return list->end;
}

bool isEmptyList (List list) {
    return iterEquals(listBegin(list), listEnd(list));
}

bool inList (List list, ListIter finding) {
    for (ListIter it = listBegin(list); iterNotEquals(it, listEnd(list)); it = iterNext(it)) {
        if (iterEquals(it, finding)) return true;
    }

    return iterEquals(finding, listEnd(list));
}

int listLength (List list) {
    int elementsCount = 0;

    for (ListIter it = listBegin(list); iterNotEquals(it, listEnd(list)); it = iterNext(it)) {
        elementsCount++;
    }

    return elementsCount;
}

bool insertToList (List list, ListIter after, ListElem value) {
    if (!inList(list, after)) return false;

    ListIter next = iterNext(after);

    ListNode newNode = createNode(value);
    after.node->next = newNode;
    newNode->next = next.node;
    next.node->prev = newNode;
    newNode->prev = after.node;

    if (iterEquals(after, listEnd(list))) list->begin = createIter(newNode);

    return true;
}

bool deleteFromList (List list, ListIter deleting) {
    if (!inList(list, deleting)) return false;
    if (iterEquals(deleting, listEnd(list))) return false;

    ListIter delPrev = iterPrev(deleting);
    ListIter delNext = iterNext(deleting);

    delPrev.node->next = delNext.node;
    delNext.node->prev = delPrev.node;

    if (iterEquals(deleting, listBegin(list))) list->begin = delNext;

    free(deleting.node);
    return true;
}

void printList (List list) {
    for (ListIter it = listBegin(list); iterNotEquals(it, listEnd(list)); it = iterNext(it)) {
        printf("%f ", iterFetch(it));
    }
}

bool expandListWithCopies (List list, ListIter copying, int lengthRequired) {
    if (!inList(list, copying)) return false;

    int lengthCurrent = listLength(list);
    if (lengthRequired < lengthCurrent) return true;

    for (int i = 0; i < lengthRequired - lengthCurrent; i++) {
        insertToList(list, copying, iterFetch(copying));
    } 

    return true;
}
