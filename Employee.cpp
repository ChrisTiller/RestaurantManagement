#include "Employee.h"
#include <cstdlib>

void fillArgs(std::vector<ColumnRowIntersection>&, std::string);
std::string trim(std::string);

Employee::Employee():
    m_employeeRecordset("C:\\Users\\Chris\\Documents\\GitHub\\RestaurantManagement\\Employees.txt", ";")
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

void fillArgs(std::vector<ColumnRowIntersection>& vecArgs, std::string args)
{
    int commaPosition = 0;
    int colonPosition = 0;
    ColumnRowIntersection cRI;

    args = trim(args);

    while ( ( commaPosition = args.find(",")) != std::string::npos )
    {
        if ( ( colonPosition = args.find(":") ) == std::string::npos )
        {
            cRI.columnName = trim(args.substr(0, commaPosition));
            cRI.rowValue = "";
        }
        else
        {
            cRI.columnName = trim(args.substr(0, colonPosition ));
            cRI.rowValue = trim(args.substr(colonPosition+1, commaPosition - colonPosition - 1 ));
        }
        vecArgs.push_back(cRI);
        args.erase(0, commaPosition + 1 );
    }

    if ( args.length() > 0 )
    {
        if ( ( colonPosition = args.find(":") ) == std::string::npos )
        {
            cRI.columnName = trim(args.substr(0, args.length()));
            cRI.rowValue = "";
        }
        else
        {
            cRI.columnName = trim(args.substr(0, colonPosition ));
            cRI.rowValue = trim(args.substr(colonPosition + 1, args.length()));
        }
        vecArgs.push_back(cRI);
    }
}


std::string trim(std::string stringToTrim)
{
    if ( stringToTrim.length() == 0 )
	{
		return "";
	}

    int position = 0;

    while ( ( position < stringToTrim.length() ) && ( stringToTrim[position] == ' ' ) )
    {
        position++;
    }

    stringToTrim = stringToTrim.erase(0, position);

    position = stringToTrim.length();

    while ( ( position >= 0 ) && ( stringToTrim[position-1] == ' ' ) )
    {
        position--;
    }

    stringToTrim = stringToTrim.erase(position, stringToTrim.length());

    return stringToTrim;
}

