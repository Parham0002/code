/**
 * @file ex24.c
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include  <string.h>

int main(){

char date [11];

char time [9];

int year, month, day, hour, minute, second;

int is_leap = 0;

printf("write the YYYY-MM-DD and HH:mm:ss :");


if (scanf("%10s %8s", date , time ) == 2){

if (strlen(date) == 10 && strlen(time) == 8){
    
     if (date[4] == '-' && date[7] == '-' && time[2] == ':' && time[5] == ':'){

            sscanf(date, "%d-%d-%d", &year, &month, &day);

                sscanf(time, "%d:%d:%d", &hour, &minute, &second);
                 
        if(year < 1 || year > 2024){

            printf("Invalid year! Must be between 1 and 2024.\n");

        }else if (month < 1 || month > 12) {

                    printf("Invalid month! Must be between 1 and 12.\n");

                } else if (day < 1 || day > 31) {

                    printf("Invalid day! Must be between 1 and 31.\n");

                } else if (hour < 0 || hour > 23) {

                    printf("Invalid hour! Must be between 0 and 23.\n");

                } else if (minute < 0 || minute > 59) {

                    printf("Invalid minute! Must be between 0 and 59.\n");

                } else if (second < 0 || second > 59) {

                    printf("Invalid second! Must be between 0 and 59.\n");

                } else {  

                    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {

                    is_leap = 1; 
                    
                }   
                    int max_day;

                    if (month == 2) {

                        max_day = is_leap ? 29 : 28; 

                    } else if (month == 4 || month == 6 || month == 9 || month == 11) {

                        max_day = 30; 

                    } else {

                        max_day = 31;
                    }
                
                     if (day > max_day) {

                        printf("Invalid day for the specified month and year!\n");

                    } else {
                        
                        printf("Date is: %s\nTime is: %s\n", date, time);

                    }
                }
            } else {

                printf("Invalid format! Please ensure date has dashes and time has colons.\n");

            }
        } else {

            printf("Wrong input! Date should be YYYY-MM-DD and Time should be HH:mm:ss.\n");

        }
    } else {

        printf("Failed to read date and time. Make sure to enter both in the correct format.\n");

    }

    return 0;
}