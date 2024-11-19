#include "bank_acc.h"

static float balance = 0.0;

void deposite(float amount)
{
    if (amount > 0)
    {
        balance += amount;
    }
}

void whitdraw(float amount)
{
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
    }
}

float get_balanced(void)
{
    return balance;
}