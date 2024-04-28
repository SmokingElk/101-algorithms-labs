#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define KEY_SIZE 6
#define VALUE_LENGTH 30

typedef struct {
    char key[KEY_SIZE];
    char value[VALUE_LENGTH];
} _Row;

typedef _Row* Row;

typedef struct {
    Row *rows;
    int rowsCount;
    int maxRowsCount;
    bool isSorted;
} _Table;

typedef _Table* Table;

Row createRow (char *key, char *value);
char* rowKey (Row row);
char* rowValue (Row row);
void deleteRow (Row row);

Table createTable (int maxRowsCount);
void deleteTable (Table table);
bool appendToTable (Table table, char *key, char *value);
void __sortTable (Table tabel, int l, int r);
void sortTable (Table table);
char* searchInTable (Table table, char *key);
void printTable (Table table);