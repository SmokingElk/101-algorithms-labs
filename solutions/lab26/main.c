#include <stdio.h>
#include "stack.h"

Stack sortStack (Stack srcStack) {
    int srcSize = sizeStack(srcStack);
    Stack res; 

    if (srcSize < 2) {
        res = createStack(srcSize);
        if (!isEmptyStack(srcStack)) pushStack(res, popStack(srcStack));
        return res;
    }

    Stack stLess = createStack(srcSize / 2);
    Stack stGreater = createStack(srcSize / 2);

    STACK_T pivot = popStack(srcStack);

    while (!isEmptyStack(srcStack)) {
        STACK_T top = popStack(srcStack);
        
        if (top <= pivot) pushStack(stLess, top);
        else pushStack(stGreater, top);
    }

    Stack stLessSorted = sortStack(stLess);
    Stack stGreaterSorted = sortStack(stGreater);

    pushStack(stLessSorted, pivot);

    res = concatStacks(stLessSorted, stGreaterSorted);

    deleteStack(stLess);
    deleteStack(stGreater);
    deleteStack(stLessSorted);
    deleteStack(stGreaterSorted);

    return res;
}

int main () {
    int elemsCount;
    printf("Input element's count: ");
    scanf("%d", &elemsCount);

    Stack stack = createStack(0);
    int elem;

    for (int i = 0; i < elemsCount; i++) {
        STACK_T elem;
        scanf("%d", &elem);
        pushStack(stack, elem);
    }

    printf("\nSource stack:\n");
    printStack(stack);

    Stack stackSorted = sortStack(stack);

    printf("\nSorted stack:\n");
    printStack(stackSorted);

    deleteStack(stack);
    deleteStack(stackSorted);

    return 0;
}