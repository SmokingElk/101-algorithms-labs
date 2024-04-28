#include <stdio.h>
#include "table.h"

#define MAX_ROWS_COUNT 10

void fillTableFromFile (Table table, char filename[]) {
    FILE *tableDataFile = fopen(filename, "r");

    char key[KEY_SIZE];
    char value[VALUE_LENGTH];

    while (fscanf(tableDataFile, "%s\n%[^$]$", key, value) == 2) {
        appendToTable(table, key, value);
    }

    fclose(tableDataFile);
}

int main () {
    Table table = createTable(MAX_ROWS_COUNT);

    fillTableFromFile(table, "rows_ordered.txt");
    printf("Rows ordered source:\n");
    printTable(table);

    sortTable(table);
    printf("Rows ordered sorted:\n");
    printTable(table);

    deleteTable(table);

    table = createTable(MAX_ROWS_COUNT);

    fillTableFromFile(table, "rows_reverse.txt");
    printf("Rows reverse source:\n");
    printTable(table);

    sortTable(table);
    printf("Rows reverse sorted:\n");
    printTable(table);

    deleteTable(table);

    table = createTable(MAX_ROWS_COUNT);

    fillTableFromFile(table, "rows_random.txt");
    printf("Rows random source:\n");
    printTable(table);

    sortTable(table);
    printf("Rows random sorted:\n");
    printTable(table);

    while (1) {
        char keyToSearch[KEY_SIZE];
        printf("Input key of value to search (EXIT - for exit): ");
        scanf("%s", keyToSearch);

        if (strcmp(keyToSearch, "EXIT") == 0) break;

        char *valueFounded = searchInTable(table, keyToSearch);
        if (valueFounded == NULL) printf("Value with key %s not found.\n", keyToSearch);
        else printf("Value for key %s is \n%s\n", keyToSearch, valueFounded);   
    }

    deleteTable(table);

    printf("Exit.\n");
    
    return 0;
}
