#include <stdio.h>
#include "bank_acc.h"

int main()
{

    deposite(100);
    printf("balance : $%.2f\n", get_balanced());

    whitdraw(30);
    printf("balance : $%.2f\n", get_balanced());

    return 0;
}