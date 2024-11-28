#include <stdio.h>
#include "linkedlist.h"

int main()
{
    link_t list;
    initList(&list);

    addd(&list, 10);
    addd(&list, 20);
    addd(&list, 30);

    printf("\n");

    printt(&list);
    printf("\n");

    removee(&list);
    printf("\n");

    printt(&list);
    printf("\n");

    removee(&list);
    printf("\n");

    printt(&list);
    printf("\n");

    removee(&list);
    printf("\n");

    printt(&list);
    printf("\n");

    removee(&list);
    printf("\n");

    destroyy(&list);

    return 0;
}