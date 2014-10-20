#include "Payroll.h"
#include <vector>

Payroll::Payroll():
    m_payroll("Payroll.txt", ";"),
    m_schedule("SchedulingHeader.txt", ";"),
    m_employees("Employees.txt", ";")
    {
        m_payroll.load();
        m_schedule.load();
        m_employees.load();
    }

void Payroll::completePayroll(string args)
{
    fillDates(m_dateFrom, m_dateThrough, args);

    if ( m_dateFrom.year == 0 || m_dateFrom.month == 0 || m_dateFrom.day == 0)
    {
        return;
    }
    if ( m_dateThrough.year == 0 || m_dateThrough.month == 0 || m_dateThrough.day == 0)
    {
        return;
    }

    m_schedule.moveFirst();

    while ( m_schedule.getRow() <= m_schedule.getRows() )
    {
        if ( isInDateRange(m_schedule.fields("Date").getRowText()) )
        {
            if ( m_schedule.fields("Payed") == "No")
            {
                if ( m_employees.containsRow("ID", m_schedule.fields("EmployeeID").getRowText()))
                {
                    if ( !m_payroll.containsRow("EmployeeID",m_schedule.fields("EmployeeID").getRowText() ))
                    {
                        m_payroll.addRow();

                        m_payroll.fields("Pay Period") = m_dateFromString + m_dateThroughString;
                        m_payroll.fields("EmployeeID") = m_employees.fields("ID");
                        m_payroll.fields("Name") = m_employees.fields("First Name").getRowText() + " " + m_employees.fields("Last Name").getRowText();
                        m_payroll.fields("Wage") = m_employees.fields("Wage");
                        m_payroll.fields("ID") = m_payroll.fields("Pay Period").getRowText() + m_payroll.fields("EmployeeID").getRowText();
                        m_payroll.fields("Hours Worked") = getHoursWorked(m_schedule.fields("EmployeeID").getRowText());
                        m_payroll.fields("Hours Payed") = m_payroll.fields("Hours Worked");
                        m_payroll.fields("Payed Amount") = double(m_employees.fields("Wage").toDouble() * m_payroll.fields("Hours Payed").toDouble());


                        m_payroll.write();
                    }

                }
                else
                {
                    cout << "employee doesn't exist" << endl;
                }
            }
        }
        m_schedule.moveNext();
    }

    makeChanges();

    m_schedule.write();
}

void Payroll::fillDates(Date& dateFrom, Date& dateThrough, string& args)
{

    int position = 0;

    if ( ( position = args.find("-") ) != std::string::npos )
    {
        string dateFromString = args.substr(0, position);
        string dateThroughString = args.substr(position+1, args.length());

        if ( ( position = dateFromString.find("/") ) != std::string::npos )
        {
            dateFrom.month = m_cal.stringToInt(dateFromString.substr(0, position ) );
            dateFromString = dateFromString.erase(0, position + 1);
            if ( ( position = dateFromString.find("/") )!= std::string::npos )
            {
                dateFrom.day = m_cal.stringToInt(dateFromString.substr(0, position));
                dateFromString = dateFromString.erase(0, position+1);

                dateFrom.year = m_cal.stringToInt(dateFromString);
            }
        }

        if ( ( position = dateThroughString.find("/") ) != std::string::npos )
        {
            dateThrough.month = m_cal.stringToInt(dateThroughString.substr(0, position ) );
            dateThroughString = dateThroughString.erase(0, position + 1);
            if ( ( position = dateThroughString.find("/") )!= std::string::npos )
            {
                dateThrough.day = m_cal.stringToInt(dateThroughString.substr(0, position));
                dateThroughString = dateThroughString.erase(0, position+1);

                dateThrough.year = m_cal.stringToInt(dateThroughString);
            }
        }

        if ( dateFrom.month == 0 || dateFrom.day == 0 || dateFrom.year == 0 )
        {
            dateFrom.month = 0;
            dateFrom.day = 0;
            dateFrom.year = 0;
            cout << "Can't parse date" << endl;
        }
        if ( dateThrough.month == 0 || dateThrough.day == 0 || dateThrough.year == 0 )
        {
            dateThrough.month = 0;
            dateThrough.day = 0;
            dateThrough.year = 0;
            cout << "Can't parse date" << endl;
        }

        if ( dateFrom.year <= dateThrough.year )
        {
            if (dateFrom.month <= dateThrough.month )
            {
                if ( dateFrom.day <= dateThrough.day )
                {
                    string fromMonthCorrector = "";
                    string throughMonthCorrector = "";
                    string fromDayCorrector = "";
                    string throughDayCorrector = "";
                    if ( dateFrom.month < 10 )
                    {
                        fromMonthCorrector = "0";
                    }
                    if ( dateFrom.day < 10 )
                    {
                        fromDayCorrector = "0";
                    }
                    if ( dateThrough.month < 10 )
                    {
                        throughMonthCorrector = "0";
                    }
                    if ( dateThrough.day < 10 )
                    {
                        throughDayCorrector = "0";
                    }
                    m_dateFromString = fromDayCorrector + m_cal.intToString(dateFrom.day) + fromMonthCorrector + m_cal.intToString(dateFrom.month) + m_cal.intToString(dateFrom.year);
                    m_dateThroughString = throughDayCorrector + m_cal.intToString(dateThrough.day) + throughMonthCorrector + m_cal.intToString(dateThrough.month) + m_cal.intToString(dateThrough.year);

                }
                else
                {
                    cout << "Invalid Date Selection" << endl;
                    dateThrough.month = 0;
                    dateThrough.day = 0;
                    dateThrough.year = 0;

                    dateFrom.month = 0;
                    dateFrom.day = 0;
                    dateFrom.year = 0;
                }
            }
            else
            {
                cout << "Invalid Date Selection" << endl;
                dateThrough.month = 0;
                dateThrough.day = 0;
                dateThrough.year = 0;

                dateFrom.month = 0;
                dateFrom.day = 0;
                dateFrom.year = 0;
            }
        }
        else
        {
            cout << "Invalid Date Selection" << endl;
            dateThrough.month = 0;
            dateThrough.day = 0;
            dateThrough.year = 0;

            dateFrom.month = 0;
            dateFrom.day = 0;
            dateFrom.year = 0;
        }


    }
    else
    {
        cout << "Can't parse dates" << endl;
    }

    if ( ( !m_cal.dateIsValid(dateFrom) ) || ( !m_cal.dateIsValid(dateThrough) ) )
    {
        dateFrom.month = 0;
        dateFrom.day = 0;
        dateFrom.year = 0;
        dateThrough.month = 0;
        dateThrough.day = 0;
        dateThrough.year = 0;

        cout << "Invalid Date" << endl;
    }


}

bool Payroll::isInDateRange(string date)
{
    Date dateToCompare;

    dateToCompare.day = stringToInt(date.substr(0, 2));
    dateToCompare.month = stringToInt(date.substr(2, 3));
    dateToCompare.year = stringToInt(date.substr(3, date.length()));

    if ( ( dateToCompare.year >= m_dateFrom.year ) && ( dateToCompare.year <= m_dateThrough.year ) )
    {
        if ( ( dateToCompare.month >= m_dateFrom.month ) && ( dateToCompare.month <= m_dateThrough.month ) )
        {
            if ( ( dateToCompare.day >= m_dateFrom.day ) && ( dateToCompare.day <= m_dateThrough.day ) )
            {
                return true;
            }
        }
    }
    return false;
}

int Payroll::getHoursWorked(string employeeID)
{

    int row = m_schedule.getRow();
    int hours = 0;

    m_schedule.moveFirst();

    while ( m_schedule.getRow() <= m_schedule.getRows() )
    {

        if ( isInDateRange(m_schedule.fields("Date").getRowText() ) )
        {
            if ( m_schedule.fields("EmployeeID") == employeeID)
            {
                if ( m_schedule.fields("Payed") == "No")
                {
                    hours += m_schedule.fields("Hours Worked").toInt();
                    m_schedule.fields("Payed") = "Yes";
                }
            }
        }
        m_schedule.moveNext();
    }

    m_schedule.moveTo(row);

    return hours;

}

void Payroll::makeChanges()
{

    string mainCommand = "";
    string rawInput = "";
    string prompt = "Command>";

    bool done = false;

    system("cls");

    string columns = "EmployeeID, Name, Wage, Hours Worked, Hours Payed, Payed Amount";

    m_payroll.printRecordset(columns);

    while ( !done )
    {
        cout << prompt;

        std::getline(std::cin, rawInput);

        system("cls");
        m_payroll.printRecordset(columns);

        Command userCommand;

        parseCommand(userCommand, rawInput);

        if ( userCommand.mainCommand == "edit" )
        {
            editPayroll(userCommand.commandArguments);
        }
        else if ( userCommand.mainCommand == "view" )
        {
            system("cls");
            m_payroll.printRecordset(columns);
        }
        else if ( userCommand.mainCommand == "help" )
        {

        }
        else if ( userCommand.mainCommand == "commit")
        {
            done = true;
        }

    }
}

void Payroll::editPayroll(string args)
{
    std::vector<ColumnRowIntersection> cRI;

    fillArgs(cRI, args);

    if ( cRI.size() != 2 )
    {
        return;
    }

    if ( cRI.at(1).columnName != "Hours Payed")
    {
        return;
    }

    if ( cRI.at(0).rowValue == "" )
    {
        std::cout << "Must specify a value search for in " << cRI.at(0).columnName << std::endl;
        return;
    }

    if ( cRI.at(1).rowValue == "" )
    {
        std::cout << "Must specify an amount of hours" << std::endl;
        return;
    }

    for ( int i = 0 ; i < cRI.size() ; i++ )
    {
        if ( !m_payroll.columnExists(cRI.at(i).columnName) )
        {
            std::cout << "Column " << cRI.at(i).columnName << " doesn't exist" << std::endl;
            return;
        }
    }

    m_payroll.moveFirst();

    while ( m_payroll.getRow() <= m_payroll.getRows() )
    {

        if ( m_payroll.fields(cRI.at(0).columnName) == cRI.at(0).rowValue )
        {

            m_payroll.fields("Hours Payed") = cRI.at(1).rowValue;
            m_payroll.fields("Payed Amount") = double(m_payroll.fields("Wage").toDouble() * m_payroll.fields("Hours Payed").toDouble());

            std::cout << "Payroll successfully edited" << std::endl;
            m_payroll.write();
            return;
        }

        m_payroll.moveNext();
    }
    std::cout << "No employee found" << std::endl;
}
