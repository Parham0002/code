#ifndef READFILE_H
#define READFILE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    FILE *fp;
} fileee;

fileee *create_fileee(const char *filename);
void fileee_message(fileee *fileee, const char *message);
void destroy_fileee(fileee *fileee);

#endif