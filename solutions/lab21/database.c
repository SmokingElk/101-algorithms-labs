#include "database.h"

DBWriter *connectDBWrite (char *filename, ConnectionResult *connectionResult) {
    DBWriter *res = malloc(sizeof(DBWriter));
    res->dbFile = fopen(filename, "w");
    res->linesWritten = 0;

    *connectionResult = res->dbFile ? CONNECTION_SUCCESS : CONNECTION_FAIL;

    return res;
}

void closeWriter (DBWriter* writer) {
    if (writer->dbFile) fclose(writer->dbFile);
    free(writer);
}

void writeNextLine (DBWriter* writer, bool hasPC, bool hasMouse, bool hasCharger) {
    ComputerSet lineData;
    lineData.id = ++writer->linesWritten;
    lineData.hasPC = hasPC;
    lineData.hasMouse = hasMouse;
    lineData.hasCharger = hasCharger;

    fwrite(&lineData, sizeof(lineData), 1, writer->dbFile);
}

int linesWritten (DBWriter* writer) {
    return writer->linesWritten;
}

DBReader *connectDBRead (char *filename, ConnectionResult *connectionResult) {
    DBReader *res = malloc(sizeof(DBReader));
    res->dbFile = fopen(filename, "r");
    res->linesRead = 0;

    *connectionResult = res->dbFile ? CONNECTION_SUCCESS : CONNECTION_FAIL;

    return res;
}

void closeReader (DBReader* reader) {
    if (reader->dbFile) fclose(reader->dbFile);
    free(reader);
}

ReadingResult readNextLine (DBReader* reader) {
    int freadRes = fread(&reader->lineData, sizeof(reader->lineData), 1, reader->dbFile);
    ReadingResult res = freadRes == 1 ? READING_CONTINUE : READING_ENDED;
    reader->linesRead++;
    return res;
}

void resetReader (DBReader* reader) {
    fseek(reader->dbFile, 0, SEEK_SET);
    reader->linesRead = 0;
}

int linesRead (DBReader* reader) {
    return reader->linesRead;
}

int columnId (DBReader* reader) {
    return reader->lineData.id;
}

bool columnHasPC (DBReader* reader) {
    return reader->lineData.hasPC;
}

bool columnHasMouse (DBReader* reader) {
    return reader->lineData.hasMouse;
}

bool columnHasCharger (DBReader* reader) {
    return reader->lineData.hasCharger;
}
