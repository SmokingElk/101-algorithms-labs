#include <stdio.h>
#include "linkedList.h"

int main () {
    List list = createList();
    insertToList(list, iterPrev(listEnd(list)), 5.0);
    insertToList(list, iterPrev(listEnd(list)), 2.0);
    insertToList(list, iterPrev(listEnd(list)), 3.0);
    insertToList(list, iterPrev(listEnd(list)), 8.0);

    printf("%d\n", lengthList(list));

    for (ListIter it = listBegin(list); iterNotEquals(it, listEnd(list)); it = iterNext(it)) {
        printf("%f ", iterFetch(it));
    }
    printf("\n");

    insertToList(list, iterNext(iterNext(listBegin(list))), 4.0);
    printList(list);
    printf("\n");

    deleteFromList(list, iterPrev(iterPrev(listEnd(list))));
    printList(list);
    printf("\n");

    deleteFromList(list, listBegin(list));
    printList(list);
    printf("\n");

    deleteFromList(list, iterPrev(listEnd(list)));
    printList(list);
    printf("\n");

    deleteFromList(list, listEnd(list));
    printList(list);
    printf("\n");

    insertToList(list, listBegin(list), 5.0);
    printList(list);
    printf("\n");

    expandListWithCopies(list, iterNext(listBegin(list)), 6);
    printList(list);
    printf("\n");

    expandListWithCopies(list, iterNext(listBegin(list)), 3);
    printList(list);
    printf("\n");

    deleteList(list);

    return 0;
}