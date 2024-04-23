#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define PARTS_COUNT 3

typedef struct {
    int id;
    bool hasPC;
    bool hasMouse;
    bool hasCharger;    
} ComputerSet;

typedef struct {
    FILE *dbFile;
    int linesWritten; 
} DBWriter;

typedef struct {
    FILE *dbFile;
    int linesRead; 
    ComputerSet lineData;
} DBReader;

typedef enum { CONNECTION_SUCCESS, CONNECTION_FAIL } ConnectionResult;
typedef enum { READING_CONTINUE, READING_ENDED } ReadingResult;

DBWriter* connectDBWrite (char *filename, ConnectionResult *connectionResult);
void closeWriter (DBWriter* writer);
void writeNextLine (DBWriter* writer, bool hasPC, bool hasMouse, bool hasCharger);
int linesWritten (DBWriter* writer);

DBReader* connectDBRead (char *filename, ConnectionResult *connectionResult);
void closeReader (DBReader* reader);
ReadingResult readNextLine (DBReader* reader);
void resetReader (DBReader* reader);
int linesRead (DBReader* reader);
int columnId (DBReader* reader);
bool columnHasPC (DBReader* reader);
bool columnHasMouse (DBReader* reader);
bool columnHasCharger (DBReader* reader);