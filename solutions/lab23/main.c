#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "BST.h"

#define HELP_KEY "help"

void printHelpMessage () {
    printf("This program process binary search trees.\n");
    printf("You will need to point out node's count and unique value for them.\n");
    printf("Program print simple topological representation of tree built.\n");
    printf("After that you will be able to delete node from your tree.\n");
    printf("Just point out a value of node, which must be deleted.\n");
    printf("If you have some difficulties, try to visit Zayka's lectures sometimes.\n");
}

int isInRange (BST tree, float rangeMin, float rangeMax) {
    if (isEmptyBST(tree)) return false;

    BST leftest = tree;
    while (leftBST(leftest) != NULL) leftest = leftBST(leftest);
    if (keyRootBST(leftest) < rangeMin) return false;

    BST rightest = tree;
    while (rightBST(rightest) != NULL) rightest = rightBST(rightest);
    if (keyRootBST(rightest) > rangeMax) return false;   

    return true;
}

int main (int argc, char const *argv[]) {
    if (argc >= 2 && strcmp(argv[1], HELP_KEY) == 0) {
        printHelpMessage();
        return 0;
    }

    int nodesCount;
    printf("Input nodes count: ");
    scanf("%d", &nodesCount);

    BST tree = NULL;
    for (int i = 0; i < nodesCount; i++) {
        float nodeValue;
        printf("Input %d node value: ", i + 1);
        scanf("%f", &nodeValue);

        while (!addToBST(&tree, newBST(nodeValue))) {
            printf("Node with value %f already exists. Input another one for %d node: ", nodeValue, i + 1);
            scanf("%f", &nodeValue);
        } 
    }

    float rangeMin, rangeMax;
    printf("Input range min: ");
    scanf("%f", &rangeMin);
    printf("Input range max: ");
    scanf("%f", &rangeMax);

    if (isInRange(tree, rangeMin, rangeMax)) printf("All values in range.\n");
    else printf("Not all values in range.\n");

    printf("Your tree:\n");
    printBST(tree, 0);

    float toDelete;
    printf("Input node's value to delete: ");
    scanf("%f", &toDelete);

    bool deleteRes = deleteNodeBST(&tree, toDelete);
    if (deleteRes) {
        printf("Successfull deletion. New tree:\n");
        printBST(tree, 0);
    } else printf("Deletion failed. Node with value %f not found.", toDelete);

    deleteBST(tree);
    return 0;
}
