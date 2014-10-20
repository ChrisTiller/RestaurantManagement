#ifndef PAYROLL_H_INCLUDED
#define PAYROLL_H_INCLUDED

#include "Calendar.h"
#include "Recordset.h"
#include <iostream>
#include <cstdlib>

using std::string;
using std::cout;
using std::endl;

class Payroll
{
public:

    Payroll();

    void completePayroll(string);
    void makeChanges();
    void editPayroll(string);

    void fillDates(Date&, Date&, string&);

    bool isInDateRange(string);

    int getHoursWorked(string);

private:

    Recordset m_payroll;
    Recordset m_schedule;
    Recordset m_employees;

    Calendar m_cal;

    Date m_dateFrom;
    Date m_dateThrough;
    string m_dateFromString;
    string m_dateThroughString;
};

#endif // PAYROLL_H_INCLUDED
