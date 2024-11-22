#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ex39.h"

#define LEN 20

void testgcd();
void testlcm();
void testsort();

int main()
{
    void testgcd();

    printf("5 tests for gcd are completed\n");

    printf("******************************\n");

    void testlcm();

    printf("5 tests for lcm are completed\n");

    printf("******************************\n");

    void testsort();

    printf("5 tests for sort are completed\n");

    printf("******************************\n");

    printf("All tests passed successfully!\n");

    return 0;
}
void testgcd()
{
    assert(gcd(8, 12) == 4);

    assert(gcd(13, 17) == 1);

    assert(gcd(35, 64) == 1);

    assert(gcd(0, 8) == 8);

    assert(gcd(1, 25) == 1);
}
void testlcm()
{
    assert(lcm(4, 6) == 12);

    assert(lcm(7, 21) == 21);

    assert(lcm(13, 17) == 221);

    assert(lcm(1, 25) == 25);

    assert(lcm(8, 8) == 8);
}
void testsort()
{

    sort("jsaNSHosAlPWnSJq");
    assert(strcmp("jsaNSHosAlPWnSJq", "AaHJjlNnoPqSSssW") == 0);

    sort("DFGSD");
    assert(strcmp("DFGSD", "DDFGS") == 0);

    sort("a1b2c3");
    assert(strcmp("a1b2c3", "123abc") == 0);

    sort("");
    assert(strcmp("", "") == 0);

    sort("@C#B!A$");
    assert(strcmp("@C#B!A$", "!#$@ABC") == 0);
}
