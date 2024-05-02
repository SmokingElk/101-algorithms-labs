#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"

void usageHint () { printf("Usage: program filename mode [param]."); }
void connectionErrorMsg () { printf("Database connection error."); }
void modeErrorMsg (char mode[]) { printf("Unexpected process mode: %s\n", mode); }

bool isSetFull (DBReader *reader, int missingForNotFull) {
    int partsIncluded = columnHasPC(reader) + columnHasMouse(reader) + columnHasCharger(reader);
    return PARTS_COUNT - partsIncluded < missingForNotFull;
}

void printAnnotation (DBReader *reader, int missingForNotFull) {
    printf("Set with id %d is ", columnId(reader));
    if (isSetFull(reader, missingForNotFull)) {
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
    if (argc < 3) {
        usageHint();
        return 1;
    }

    int notFullSetsCount = 0;
    ConnectionResult connectionRes;
    DBReader *reader = connectDBRead(argv[1], &connectionRes);

    if (connectionRes != CONNECTION_SUCCESS) {
        connectionErrorMsg();
        return 2;
    } 

    if (strcmp(argv[2], "-f") == 0) {
        while (readNextLine(reader) == READING_CONTINUE) {
            printf("%d\t%d\t%d\t%d\n", columnId(reader), columnHasPC(reader), columnHasMouse(reader), columnHasCharger(reader));
        }

        return 0;
    }

    if (strcmp(argv[2], "-p") != 0) {
        modeErrorMsg(argv[2]);
        return 1;
    }

    int missingForNotFull = atoi(argv[3]);

    while (readNextLine(reader) == READING_CONTINUE) {
        if (isSetFull(reader, missingForNotFull)) continue;

        printAnnotation(reader, missingForNotFull);
        notFullSetsCount++;
    }

    if (notFullSetsCount == 0) printf("No");
    else printf("%d", notFullSetsCount);
    printf(" sets with missing parts.");

    closeReader(reader);
    return 0;
}