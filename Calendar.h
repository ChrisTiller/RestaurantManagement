#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

#include <iostream>

#ifndef NULL
#define  NULL 0
#endif // NULL

struct Date
{
    // nulls used to make sure date is correctly parsed
    int month = 0;
    int year = 0;
    int day = 0;
};

class Calendar
{
public:

    void printCalendar(std::string);

    int getStartingDayOfMonth(int,int);
    int getDaysInMonth(int,int);
    bool isLeapYear(int);

private:
    Date parseDateFromString(std::string);
    int stringToInt(std::string);
};

#endif // CALENDAR_H_INCLUDED
