#include "Employee.h"
#include <cstdlib>

Employee::Employee():
    m_employeeRecordset("C:\\Users\\Chris\\Documents\\GitHub\\RestaurantManagement\\inventory.txt", ";")
{
    m_employeeRecordset.load();
}

Employee::~Employee()
{
}

void Employee::addEmployee(std::string args)
{

    std::vector<ColumnRowIntersection> columnAndValues;

    fillArgs(columnAndValues, args);

    if ( columnAndValues.size() == 0 )
    {
        return;
    }

    int position = 0;

    for ( int i = 0 ; i < columnAndValues.size() ; i++ )
    {
        if ( !m_employeeRecordset.columnExists(columnAndValues.at(i).columnName) )
        {
            std::cout << "Column " << columnAndValues.at(i).columnName << " doesn't exist." << std::endl;
            return;
        }
    }

    m_employeeRecordset.addRow();

    for ( int i = 0 ; i < columnAndValues.size() ; i++ )
    {
            m_employeeRecordset.fields(columnAndValues.at(i).columnName) = columnAndValues.at(i).rowValue;
    }

    m_employeeRecordset.write();

    std::cout << "Employee added" << std::endl;

}

void Employee::removeEmployee(std::string args)
{

    std::vector<ColumnRowIntersection> columnsAndValue;

    fillArgs(columnsAndValue, args);

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

void Employee::editEmployee(std::string column)
{

    if ( !m_employeeRecordset.columnExists(column) )
    {
        return;
    }

    m_employeeRecordset.moveFirst();

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
            std::cout << "Column " << cRI.at(i).columnName << " doesn't exist." << std::endl;
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



