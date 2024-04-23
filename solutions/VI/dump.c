#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"

void usageHint () { printf("Usage: program filename."); }
void errorMsg () { printf("Database connection error."); }

int main (int argc, char *argv[]) {  
    if (argc != 2) {
        usageHint();
        return 1;
    }

    ConnectionResult connectionRes;
    DBWriter *writer = connectDBWrite(argv[1], &connectionRes);

    if (connectionRes != CONNECTION_SUCCESS) {
        errorMsg();
        return 2;
    } 

    int hasPC, hasMouse, hasCharger;
    
    while (scanf("%d\t%d\t%d\n", &hasPC, &hasMouse, &hasCharger) == 3) {
        writeNextLine(writer, hasPC, hasMouse, hasCharger);
    }

    closeWriter(writer);
    return 0;
}