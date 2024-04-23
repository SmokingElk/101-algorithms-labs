#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"

void usageHint () { printf("Usage: program filename."); }
void errorMsg () { printf("Database connection error."); }

bool isSetFull (DBReader *reader) {
    return columnHasPC(reader) && columnHasMouse(reader) && columnHasCharger(reader);
}

void printAnnotation (DBReader *reader) {
    printf("Set with id %d is ", columnId(reader));
    if (isSetFull(reader)) {
        printf("full.\n");
        return;
    }

    printf("not full. Missing: ");

    bool hasParts[PARTS_COUNT] = {columnHasPC(reader), columnHasMouse(reader), columnHasCharger(reader)};
    char *partsNames[PARTS_COUNT] = {"PC", "mouse", "charger"};

    bool wasPrint = false;
    for (int i = 0; i < PARTS_COUNT; i++) {
        if (hasParts[i]) continue;

        if (wasPrint) printf(", ");
        else wasPrint = true;

        printf("%s", partsNames[i]);
    }

    printf(".\n");
}

int main (int argc, char *argv[]) {  
    if (argc != 2) {
        usageHint();
        return 1;
    }

    int notFullSetsCount = 0;
    ConnectionResult connectionRes;
    DBReader *reader = connectDBRead(argv[1], &connectionRes);

    if (connectionRes != CONNECTION_SUCCESS) {
        errorMsg();
        return 2;
    } 

    while (readNextLine(reader) == READING_CONTINUE) {
        if (isSetFull(reader)) continue;

        printAnnotation(reader);
        notFullSetsCount++;
    }

    if (notFullSetsCount == 0) printf("No");
    else printf("%d", notFullSetsCount);
    printf(" sets with missing parts.");

    closeReader(reader);
    return 0;
}