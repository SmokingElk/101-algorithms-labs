#include "table.h"

Row createRow (char *key, char *value) {
    Row res = (Row)malloc(sizeof(_Row));
    strcpy(res->key, key);
    strcpy(res->value, value);
    return res;
}

char* rowKey (Row row) {
    return row->key;
}

char* rowValue (Row row) {
    return row->value;
}

void deleteRow (Row row) {
    free(row);
}

Table createTable (int maxRowsCount) {
    Table res = (Table)malloc(sizeof(_Table));

    res->rowsCount = 0;
    res->maxRowsCount = maxRowsCount;
    res->isSorted = true;

    res->rows = (Row*)malloc(sizeof(Row) * maxRowsCount);

    return res;
}

void deleteTable (Table table) {
    for (int i = 0; i < table->rowsCount; i++) {
        deleteRow(table->rows[i]);
    }
    
    free(table->rows);
    free(table);
}

bool appendToTable (Table table, char *key, char *value) {
    if (table->rowsCount >= table->maxRowsCount) return false;

    table->rows[table->rowsCount++] = createRow(key, value);
    table->isSorted = false;
    return true;
}

void __sortTable (Table tabel, int l, int r) {
    if (r - l < 2) return;

    int i = l, j = r - 1; 
    char *pivot = rowKey(tabel->rows[(l + r) / 2]);

    while (i <= j) {
        while (strcmp(rowKey(tabel->rows[i]), pivot) < 0) i++;
        while (strcmp(rowKey(tabel->rows[j]), pivot) > 0) j--;

        if (i <= j) {
            Row tmp = tabel->rows[i];
            tabel->rows[i] = tabel->rows[j];
            tabel->rows[j] = tmp;

            i++;
            j--;
        }
    }

    __sortTable(tabel, l, j + 1);
    __sortTable(tabel, i, r);
}

void sortTable (Table table) {
    if (table->isSorted) return;
    __sortTable(table, 0, table->rowsCount);
    table->isSorted = true;
}

char* searchInTable (Table table, char *key) {
    if (!table->isSorted) sortTable(table);

    int l = 0, r = table->rowsCount - 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        char *midKey = rowKey(table->rows[mid]);

        int cmpRes = strcmp(key, midKey);

        if (cmpRes < 0) r = mid - 1; 
        else if (cmpRes > 0) l = mid + 1;
        else return rowValue(table->rows[mid]);
    }
    
    return NULL;
}

void printTable (Table table) {
    for (int i = 0; i < table->rowsCount; i++) {
        Row row = table->rows[i];
        printf("%s\n%s\n", rowKey(row), rowValue(row));
    }
}