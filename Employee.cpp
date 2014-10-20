#include "Employee.h"
#include <cstdlib>

Employee::Employee():
    m_employeeRecordset("Employees.txt", ";")
{
    m_employeeRecordset.load();
    m_employeeRecordset.setAutoIncrement(true);
}

Employee::~Employee()
{
}

void Employee::addEmployee(std::string args)
{
    // create vector to hold all the columns with the respect row values
    std::vector<ColumnRowIntersection> columnAndValues;

    // fills vector from string argument given in the parameters
    fillArgs(columnAndValues, args);

    // checks to make sure user actually put in any information
    if ( columnAndValues.size() == 0 )
    {
        return;
    }

    int position = 0;

    // makes sure that all the columns they want put information in exists
    for ( int i = 0 ; i < columnAndValues.size() ; i++ )
    {
        if ( !m_employeeRecordset.columnExists(columnAndValues.at(i).columnName) )
        {
            std::cout << "Column " << columnAndValues.at(i).columnName << " doesn't exist." << std::endl;
            return;
        }
    }

    m_employeeRecordset.addRow();

    // for all the columns in vector, select the correct column and change the default value to the user defined one
    for ( int i = 0 ; i < columnAndValues.size() ; i++ )
    {
            m_employeeRecordset.fields(columnAndValues.at(i).columnName) = columnAndValues.at(i).rowValue;
    }

    int position2 = 0;

    if ( m_employeeRecordset.fields("Wage") == "")
    {
        m_employeeRecordset.fields("Wage") = "7.25";
    }


    m_employeeRecordset.write();

    std::cout << "Employee added" << std::endl;

}

void Employee::removeEmployee(std::string args)
{

    std::vector<ColumnRowIntersection> columnsAndValue;

    fillArgs(columnsAndValue, args);

    if ( columnsAndValue.size() == 0 )
    {
        return;
    }

    for ( int i = 0 ; i < columnsAndValue.size() ; i++)
    {

        if ( !m_employeeRecordset.columnExists(columnsAndValue.at(i).columnName) )
        {
            std::cout << "Column " << columnsAndValue.at(i).columnName << " doen't exist." << std::endl;
            return;
        }
        else
        {
            if ( columnsAndValue.at(i).rowValue == "" )
            {
                std::cout << "Must specify a value to search by for " << columnsAndValue.at(i).columnName << std::endl;
                return;
            }
        }

    }

    m_employeeRecordset.moveFirst();

    int counter = 0;

    while ( m_employeeRecordset.getRow() <= m_employeeRecordset.getRows() )
    {
        counter = 0;

        for ( int i = 0 ; i < columnsAndValue.size() ; i++ )
        {
            if ( m_employeeRecordset.fields(columnsAndValue.at(i).columnName) == columnsAndValue.at(i).rowValue )
            {
                counter++;
            }
        }

        if ( counter == columnsAndValue.size() )
        {
            m_employeeRecordset.removeRow();
            m_employeeRecordset.write();
            return;
        }

        m_employeeRecordset.moveNext();
    }
}

void Employee::editEmployee(std::string args)
{
    std::vector<ColumnRowIntersection> cRI;

    fillArgs(cRI, args);

    if ( cRI.size() == 0 )
    {
        return;
    }

    if ( cRI.at(0).rowValue == "" )
    {
        std::cout << "Must specify a value to search for in " << cRI.at(0).columnName << std::endl;
    }

    for ( int i = 0 ; i < cRI.size() ; i++ )
    {
        if ( !m_employeeRecordset.columnExists(cRI.at(i).columnName) )
        {
            std::cout << "Column " << cRI.at(i).columnName << " doesn't exist" << std::endl;
            return;
        }
    }

    m_employeeRecordset.moveFirst();

    while ( m_employeeRecordset.getRow() <= m_employeeRecordset.getRows() )
    {

        if ( m_employeeRecordset.fields(cRI.at(0).columnName) == cRI.at(0).rowValue )
        {
            for ( int i = 1 ; i < cRI.size() ; i++ )
            {
                m_employeeRecordset.fields(cRI.at(i).columnName) = cRI.at(i).rowValue;
            }
            std::cout << "Employee successfully edited" << std::endl;
            m_employeeRecordset.write();
            return;
        }

        m_employeeRecordset.moveNext();
    }
    std::cout << "No employee found" << std::endl;
    return;
}

void Employee::viewEmployees(std::string args)
{

    system("cls");

    std::vector<ColumnRowIntersection> cRI;

    fillArgs(cRI, args);

    for ( int i = 0 ; i < cRI.size() ; i++)
    {
        if ( !m_employeeRecordset.columnExists(cRI.at(i).columnName) )
        {
            std::cout << "Column " << cRI.at(i).columnName << " doesn't exist" << std::endl;
            return;
        }
    }

    m_employeeRecordset.printRecordset(args);
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



