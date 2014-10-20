#ifndef SCHEDULING_H_INCLUDED
#define SCHEDULING_H_INCLUDED

#include <iostream>
#include "Calendar.h"
#include "Recordset.h"

class Schedules
{
public:

    Schedules();
    //~Schedules();

    Date parseDate(std::string);

    void viewCalendar(Date);
    void viewCalendar(std::string);

    void scheduleEmployees();

private:

    Calendar m_cal;

    Recordset m_scheduleHeader;
    Recordset m_scheduleDetail;
    Recordset m_employees;

    Date currentDate;
};


#endif // SCHEDULING_H_INCLUDED
