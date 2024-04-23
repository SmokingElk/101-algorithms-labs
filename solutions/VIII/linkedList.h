#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef float ListElem;

typedef struct __ListNode {
    ListElem value;
    struct __ListNode *next;
    struct __ListNode *prev;
} _ListNode;

typedef _ListNode* ListNode;

typedef struct {
    ListNode node;
} ListIter;

typedef struct {
    ListIter begin;
    ListIter end;
} _List;

typedef _List* List;

ListNode createNode (ListElem value);
void deleteNode (ListNode node);

ListIter createIter (ListNode node);
ListIter iterNext (ListIter iter);
ListIter iterPrev (ListIter iter);
bool iterEquals (ListIter iter1, ListIter iter2);
bool iterNotEquals (ListIter iter1, ListIter iter2);
ListElem iterFetch (ListIter iter);
void iterStore (ListIter iter, ListElem value);

List createList ();
void deleteList (List list);
ListIter listBegin (List list);
ListIter listEnd (List list);
bool isEmptyList (List list);
int listLength (List list);
bool inList (List list, ListIter finding);
bool insertToList (List list, ListIter after, ListElem value);
bool deleteFromList (List list, ListIter deleting);
void printList (List list);
bool expandListWithCopies (List list, ListIter copying, int lengthRequired);