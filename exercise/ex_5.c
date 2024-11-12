#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){
//char
   printf("char:\n\tSize: %zu bytes\n\tMin: %d\n\tMax: %d\n\n", sizeof(char), CHAR_MIN, CHAR_MAX);
   printf("signed char:\n\tSize: %zu bytes\n\tMin: %d\n\tMax: %d\n\n", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
   printf("unsigned char:\n\tSize: %zu bytes\n\tMin: 0\n\tMax: %d\n\n", sizeof(unsigned char), UCHAR_MAX);
//int
   printf("int:\n\tSize: %zu bytes\n\tMin: %d\n\tMax: %d\n\n", sizeof(int), INT_MIN, INT_MAX);
   printf("unsigned int:\n\tSize: %zu bytes\n\tMin: 0\n\tMax: %u\n\n", sizeof(unsigned int),UINT_MAX);
   printf("short int:\n\tSize: %zu bytes\n\tMin: %d\n\tMax: %d\n\n", sizeof(short int),SHRT_MIN,SHRT_MAX);
   printf("unsigned short int:\n\tSize: %zu bytes\n\tMin: 0\n\tMax: %u\n\n", sizeof(unsigned short int),USHRT_MAX);
   printf("signed long int:\n\tSize %zu bytes\n\tMin: %ld\n\tMax: %ld\n\n", sizeof(signed long int),LONG_MIN,LONG_MAX);
   printf("unsigned long int:\n\tSize: %zu bytes\n\tMin: 0\n\tMax: %lu\n\n",sizeof(unsigned long int),ULONG_MAX);
   printf("signed long long int:\n\tSize: %zu bytes\n\tMin: %lld\n\tMax: %lld\n\n",sizeof(signed long long int),LLONG_MIN,LLONG_MAX);
   printf("unsigned long long int: \n\tSize: %zu bytes\n\tMin: 0\n\tMax: %llu\n\n", sizeof(unsigned long long int),ULLONG_MAX);
//float
   printf("float:\n\tSize: %zu bytes\n\tMin: %e\n\tMax: %e\n\n", sizeof(float), FLT_MIN, FLT_MAX);
   printf("double:\n\tSize: %zu bytes\n\tMin: %e\n\tMax: %e\n\n", sizeof(double), DBL_MIN, DBL_MAX);
   printf("long double:\n\tSize: %zu bytes\n\tMin: %Lg\n\tMax: %Lg\n\n", sizeof(long double), LDBL_MIN, LDBL_MAX);
//enum
   enum color { RED, GREEN, BLUE, YELLOW, WHITE, BLACK };
   printf("enum\n\tSize: %zu bytes\n\n", sizeof(enum color));

   return 0;

}