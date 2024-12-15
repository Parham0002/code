#include <stdio.h>
#include <stdint.h>
#include "readfile.h"

int main()
{

    fileee *file = create_fileee("text.txt");

    fileee_message(file, "hello world");

    destroy_fileee(file);

    return 0;
}