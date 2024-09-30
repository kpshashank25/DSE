#include <stdio.h> 
int check(int day, int month) 
{ 
if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) 
{ 
return 1; 
} return 0; 
} int isleap(int year) 
{ if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
{ 
return 1; 
} return 0; 

 } 
int days_in_month(int month, int year) 
{ 
switch (month) 
{ case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31; case 4: case 6: case 9: case 11: return 30; case 2: 
return isleap(year) ? 29 : 28; 
} 
} 
int main()
 {
 int day, month, year;
 printf("Enter the date in the form of DD-MM-YYYY: "); 
scanf("%d-%d-%d", &day, &month, &year); 
if (year < 1) { printf("Invalid year\n"); return 1; } 
if (month < 1 || month > 12 || check(day, month) || day < 1 || day > days_in_month(month, year))
 { 
printf("Invalid date\n"); 
return 1; 
} 
day++; 
if (day > days_in_month(month, year)) 
{ day = 1; month++; if (month > 12) 
{ 
month = 1; year++; } }
 if (year > 2012) 
{ printf("Out of range\n");
 return 1; 
} 
printf("The next day is: %02d-%02d-%d\n", day, month, year); 
return 0; 
} 











