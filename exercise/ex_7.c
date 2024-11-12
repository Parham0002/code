#include <stdio.h>
#include <string.h>

typedef struct {

    int day;

    int month;

    int year;

} date_t;

int main(void){

    date_t date;
    printf("what day is it?");
    scanf("%d",&date.day);

    printf("what month is it?");
    scanf("%d",&date.month);

    printf("what year is it?");
    scanf("%d", &date.year);

    printf("date for today is:\n %02d - %02d - %04d\n", date.day,date.month,date.year);


}