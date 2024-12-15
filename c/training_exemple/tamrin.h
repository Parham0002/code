#ifndef TAMRIN_H
#define TAMRIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "recordd.bin"
#define SIZE_LEN 50
#define SINGLE_RECORD 1
#define ZERO 0
#define ONE 1

typedef struct
{
    char name[SIZE_LEN];
    int id;

} Recordd;

void create_record(const char *filename);

void read_record(const char *filename);

void update_record(const char *filename, int id, const char *newname);

void delete_record(const char *filename, int id);

#endif