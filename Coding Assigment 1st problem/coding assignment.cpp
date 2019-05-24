#include <iostream>
using namespace std;
int perYear(int day, bool isLeap){ // this function computes number of sundays that fell on first day of month per some particular year
    int res=0;
    for(int i=1;i<13;i++){
        if( i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12 ) day +=3; // after 31 days weekday is moved to 3
        else if ( i == 4 || i == 6 || i == 9 || i == 11 ) day += 2; // after 30 - 2
        else if ( isLeap ) day += 1; // after 29 - 1 (leap year)
        day = day % 7; // after 28 days - 0 days
        if(day == 0) res++; // 1 - Mon, 2 - Tue; 3 - Thu, ... , 6 - Sat, 0 - Sun
    }
    return res;
}
int main(){
    int day = 1; // 1 Jan of 1900 - Mon 
    // 1 - Mon, 2 - Tue; 3 - Thu, ... , 6 - Sat, 0 - Sun
    day = (day + 365) % 7; // 1 Jan of 1901 - Tue; 1900 is not a leap year, check for it is omitted
    int res = 0;
    for(int year = 1901; year<2001; year++){
        bool isLeap = ( year % 400==0 || (year % 100 != 0 && year % 4 == 0));
        res += perYear(day, isLeap);
        if(isLeap) day +=2;
        else day +=1;
        day = day % 7;
    }
    cout << res;
}