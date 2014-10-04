#include "Employee.h"


Employee::Employee():
    m_employeeRecordset("Employees.txt", ";")
{
    m_employeeRecordset.loadFromFile();
}

Employee::~Employee()
{
    m_employeeRecordset.writeToFile();
}

void Employee::addEmployee(std::string args)
{

    m_employeeRecordset.addRow();

    m_employeeRecordset.fields("FNAME") = args;
    m_employeeRecordset.fields("LNAME") = args;
    m_employeeRecordset.fields("PHONE") = args;
    m_employeeRecordset.fields("ADDRESS") = args;
    m_employeeRecordset.fields("WAGE") = args;

}

void Employee::removeEmployee(std::string column, std::string valueToSearch)
{
    m_employeeRecordset.moveFirst();

    if ( !m_employeeRecordset.columnExists(column) )
    {
        return;
    }

    while ( m_employeeRecordset.getRow() <= m_employeeRecordset.getRows() )
    {
        if ( m_employeeRecordset.fields(column) == valueToSearch )
        {
            m_employeeRecordset.removeRow();
            return;
        }
        m_employeeRecordset.moveNext();
    }
}

void Employee::editEmployee(std::string column, std::string valueToSearch, std::string firstName, std::string lastName, std::string phone, std::string address, std::string wage)
{

    if ( !m_employeeRecordset.columnExists(column) )
    {
        return;
    }

    m_employeeRecordset.moveFirst();

    while ( m_employeeRecordset.getRow() <= m_employeeRecordset.getRows() )
    {
        if ( m_employeeRecordset.fields(column) == valueToSearch )
        {
            m_employeeRecordset.fields("FNAME") = firstName;
            m_employeeRecordset.fields("LNAME") = lastName;
            m_employeeRecordset.fields("PHONE") = phone;
            m_employeeRecordset.fields("ADDRESS") = address;
            m_employeeRecordset.fields("WAGE") = wage;
            return;
        }
        m_employeeRecordset.moveNext();
    }
}

void Employee::viewEmployees(std::string columns)
{

    std::vector<std::string> columnNames;

    int position = 0;

    while ( ( position = columns.find(",")) != std::string::npos )
    {

        columnNames.push_back(trim(columns.substr(0, position)));
        columns.erase(0, position + 1 );

    }

    std::cout << columnNames.at(0) << std::endl;

    if ( !m_employeeRecordset.columnExists(columns) )
    {
        return;
    }

    DataColumn* cols = m_employeeRecordset.getFirstColumn();

    std::cout << m_employeeRecordset.fields(columns).getColumnName() << std::endl;

    m_employeeRecordset.moveFirst();

    while ( m_employeeRecordset.getRow() <= m_employeeRecordset.getRows() )
    {

        std::cout << m_employeeRecordset.fields(columns) << std::endl;
        m_employeeRecordset.moveNext();
    }

}

bool Employee::employeeExists(std::string column, std::string value)
{

     m_employeeRecordset.moveFirst();

    while ( m_employeeRecordset.getRow() <= m_employeeRecordset.getRows() )
    {
        if ( m_employeeRecordset.fields(column) == value )
        {
           return true;
        }
        m_employeeRecordset.moveNext();
    }
    return false;
}

std::string trim(std::string stringToTrim)
{

    int position = 0;

    while ( ( position < stringToTrim.length() ) && ( stringToTrim[position] == ' ' ) )
    {
        position++;
    }

    stringToTrim = stringToTrim.erase(0, position);

    position = stringToTrim.length();

    while ( ( position >= 0 ) && ( stringToTrim[position] == ' ' ) )
    {
        position--;
    }

    stringToTrim = stringToTrim.erase(position-1, stringToTrim.length());

    return stringToTrim;

}

