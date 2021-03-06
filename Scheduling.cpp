#include "Scheduling.h"
#include "helperFile.h"
#include <cstdlib>

Schedules::Schedules():
    m_scheduleHeader("SchedulingHeader.txt", ";"),
    m_scheduleDetail("SchedulingDetail.txt", ";"),
    m_employees("Employees.txt", ";")
    {
        m_scheduleHeader.load();
        m_scheduleDetail.load();
        m_scheduleDetail.setAutoIncrement(true);
        m_employees.load();
    }

Date Schedules::parseDate(std::string stringDate)
{
    return m_cal.parseDateFromString(stringDate);
}

void Schedules::viewCalendar(Date calendarMonth)
{
    if ( calendarMonth.month == 0 || calendarMonth.year == 0)
    {
        return;
    }

    system("cls");

    m_cal.printCalendar(calendarMonth.month, calendarMonth.year);

    currentDate.month = calendarMonth.month;
    currentDate.year = calendarMonth.year;

    std::string rawInput;

    std::cout << "Enter the number of the day you want to choose" << std::endl;

    std::getline(std::cin, rawInput);

    int day = m_cal.stringToInt(rawInput);


    if ( ( day > 0 ) && ( day < m_cal.getDaysInMonth(calendarMonth.month, calendarMonth.year) ) )
    {
        currentDate.day = day;

        std::string monthCorrector = "";
        std::string dayCorrector = "";
        if ( currentDate.month < 10 )
        {
            monthCorrector = "0";
        }
        if ( currentDate.day < 10 )
        {
            dayCorrector = "0";
        }

        ColumnRowIntersection temp;

        temp.columnName = "Date";
        temp.rowValue = dayCorrector + m_cal.intToString(currentDate.day) + monthCorrector + m_cal.intToString(currentDate.month) + m_cal.intToString(currentDate.year);

        std::vector<ColumnRowIntersection> dateField;

        dateField.push_back(temp);

        string hourCorrector, nextHourCorrector;

        if ( !m_scheduleDetail.containsRow(dateField) )
        {
            for ( int i = 1 ; i < 24 ; i++ )
            {
                if ( i < 10  )
                {
                    hourCorrector = "0";
                }
                if ( (i+1) < 10 )
                {
                    nextHourCorrector = "0";
                }
                std::cout << hourCorrector << i << ":00-" << nextHourCorrector << i+1 << ":00" << std::endl;

                hourCorrector = "";
                nextHourCorrector = "";
            }

            scheduleEmployees();
        }
        else
        {
            ColumnRowIntersection time;
            time.columnName = "Time";

            for ( int i = 1  ; i < 24 ; i++  )
            {
                dateField.clear();
                dateField.push_back(temp);
                time.rowValue = m_cal.intToString(i);

                dateField.push_back(time);

                if ( i < 10 )
                {
                    hourCorrector = "0";
                }
                if ( (i+1) < 10 )
                {
                    nextHourCorrector = "0";
                }

                if (  m_scheduleDetail.containsRow(dateField) )
                {
                    if ( m_employees.containsRow("ID", m_scheduleDetail.fields("EmployeeID").getRowText() ))
                    {
                            std::cout << hourCorrector << i << ":00-" << nextHourCorrector << i+1 << ":00" << " " << m_employees.fields("First Name") << " " << m_employees.fields("Last Name") << std::endl;
                    }
                }
                else
                {
                    std::cout << hourCorrector << i << ":00-" << nextHourCorrector << i+1 << ":00" << std::endl;
                }

                hourCorrector = "";
                nextHourCorrector = "";
            }

            scheduleEmployees();
        }

    }
    else
    {
        std::cout << "Invalid date selection" << std::endl;
    }

}

void Schedules::viewCalendar(std::string args)
{

    Date calendarDate = parseDate(args);

    viewCalendar(calendarDate);

}

void Schedules::scheduleEmployees()
{

    std::string mainCommand = "";
    std::string rawInput = "";
    std::string prompt = "Command>";

    bool done = false;
    bool canContinue = true;

    while ( !done )
    {
        canContinue = true;

        std::cout << prompt;
        getline(std::cin, rawInput);

        Command userCommand;

        parseCommand(userCommand, rawInput);

        if ( userCommand.mainCommand == "add" )
        {
            std::vector<ColumnRowIntersection> cRI;

            fillArgs(cRI, userCommand.commandArguments);

            ColumnRowIntersection workHour = cRI.at(cRI.size()-1);

            cRI.erase(cRI.begin()+ (cRI.size()-1));

            for ( int i = 0 ; i < cRI.size() ; i++ )
            {
                if ( !m_employees.columnExists(cRI.at(i).columnName) )
                {
                    std::cout << "Column " << cRI.at(i).columnName << " doesn't exist" << std::endl;
                    canContinue = false;
                }
            }

            if ( !m_scheduleDetail.columnExists(workHour.columnName) )
            {
                std::cout << "Column " << workHour.columnName << " doesn't exist" << std::endl;
                canContinue = false;
            }

            if ( ( m_cal.stringToInt(workHour.rowValue) < 0 ) || ( m_cal.stringToInt(workHour.rowValue) > 25 ) )
            {
                std::cout << "Invalid work time" << std::endl;
                canContinue = false;
            }

            if ( !m_employees.containsRow(cRI))
            {
                std::cout << "Can't find employee" << std::endl;
                canContinue = false;
            }

            if ( canContinue )
            {
                std::string monthCorrector = "";
                std::string dayCorrector = "";
                if ( currentDate.month < 10 )
                {
                    monthCorrector = "0";
                }
                if ( currentDate.day < 10 )
                {
                    dayCorrector = "0";
                }

                cRI.clear();

                ColumnRowIntersection temp;

                temp.columnName = "Date";
                temp.rowValue = dayCorrector + m_cal.intToString(currentDate.day) + monthCorrector + m_cal.intToString(currentDate.month) + m_cal.intToString(currentDate.year);

                cRI.push_back(temp);

                temp.columnName = "Time";
                temp.rowValue = workHour.rowValue;

                cRI.push_back(temp);

                if ( !m_scheduleDetail.containsRow(cRI) )
                {
                    m_scheduleDetail.addRow();

                    m_scheduleDetail.fields("Date") = dayCorrector + m_cal.intToString(currentDate.day) + monthCorrector + m_cal.intToString(currentDate.month) + m_cal.intToString(currentDate.year);
                    m_scheduleDetail.fields("EmployeeID") = m_employees.fields("ID");
                    m_scheduleDetail.fields("First Name") = m_employees.fields("First Name");
                    m_scheduleDetail.fields("Last Name") = m_employees.fields("Last Name");
                    m_scheduleDetail.fields("Time") = workHour.rowValue;


                    temp.columnName = "ID";
                    temp.rowValue = dayCorrector + m_cal.intToString(currentDate.day) + monthCorrector + m_cal.intToString(currentDate.month) + m_cal.intToString(currentDate.year) + m_employees.fields("ID").getRowText();

                    std::vector<ColumnRowIntersection> employee;

                    employee.push_back(temp);

                    if ( m_scheduleHeader.containsRow(employee))
                    {
                        int currentHours = m_scheduleHeader.fields("Hours Worked").toInt();
                        currentHours += 1;
                        m_scheduleHeader.fields("Hours Worked") = currentHours;
                    }
                    else
                    {
                        m_scheduleHeader.addRow();

                        m_scheduleHeader.fields("ID") = dayCorrector + m_cal.intToString(currentDate.day) + monthCorrector + m_cal.intToString(currentDate.month) + m_cal.intToString(currentDate.year) + m_employees.fields("ID").getRowText();
                        m_scheduleHeader.fields("EmployeeID") = m_employees.fields("ID");
                        m_scheduleHeader.fields("Hours Worked") = 1;
                        m_scheduleHeader.fields("Payed") = "No";
                        m_scheduleHeader.fields("Date") = dayCorrector + m_cal.intToString(currentDate.day) + monthCorrector + m_cal.intToString(currentDate.month) + m_cal.intToString(currentDate.year);
                    }
                    m_scheduleHeader.write();
                    m_scheduleDetail.write();
                }
                else
                {
                    std::cout << "Time has already been filled by another employee" << std::endl;
                }
            }

        }
        else if ( userCommand.mainCommand == "remove" )
        {
            std::vector<ColumnRowIntersection> cRI;

            fillArgs(cRI, userCommand.commandArguments);

            if ( cRI.size() > 1 )
            {
                std::cout << "Too many arguments" << std::endl;
                canContinue = false;
            }

            if ( cRI.at(0).columnName != "Time" )
            {
                std::cout << "Need time column" << std::endl;
                canContinue = false;
            }

            if ( ( m_cal.stringToInt(cRI.at(0).rowValue) < 0 ) || ( m_cal.stringToInt(cRI.at(0).rowValue) > 25 ) )
            {
                std::cout << "Invalid work time" << std::endl;
                canContinue = false;
            }



            if ( canContinue )
            {

                std::string monthCorrector = "";
                std::string dayCorrector = "";
                if ( currentDate.month < 10 )
                {
                    monthCorrector = "0";
                }
                if ( currentDate.day < 10 )
                {
                    dayCorrector = "0";
                }

                ColumnRowIntersection temp;

                temp.columnName = "Date";

                temp.rowValue = dayCorrector + m_cal.intToString(currentDate.day) + monthCorrector + m_cal.intToString(currentDate.month) + m_cal.intToString(currentDate.year);

                cRI.push_back(temp);

                if ( m_scheduleDetail.containsRow(cRI))
                {
                    if ( m_scheduleHeader.containsRow("ID", temp.rowValue + m_scheduleDetail.fields("EmployeeID").getRowText()))
                    {
                        if ( m_scheduleDetail.fields("Hours Work") == "1" )
                        {
                            m_scheduleHeader.removeRow();
                        }
                        else
                        {
                            m_scheduleHeader.fields("Hours Worked") = m_scheduleHeader.fields("Hours Worked").toInt() - 1;
                        }

                        m_scheduleHeader.write();
                    }
                    m_scheduleDetail.removeRow();
                    m_scheduleDetail.write();
                }
            }
        }
        else if ( userCommand.mainCommand == "calendar" )
        {
            viewCalendar(userCommand.commandArguments);
            done = true;
        }
        else if ( userCommand.mainCommand == "exit" )
        {
            done = true;
        }
        else if ( userCommand.mainCommand == "help" )
        {
            std::cout << "add <employee to add information>, ..., <time:hour>" << std::endl;
            std::cout << "remove <time:hour> " << std::endl;
            std::cout << "exit" << std::endl;
        }
        else
        {
            std::cout << "Unknown command: " << userCommand.mainCommand << std::endl;
            std::cout << "Enter help for a list of commands" << std::endl;
        }

    }



}
