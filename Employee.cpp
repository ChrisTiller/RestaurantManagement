#include "Employee.h"
#include <cstdlib>

Employee::Employee():
    m_employeeRecordset("C:\\Users\\Chris\\Documents\\GitHub\\RestaurantManagement\\Employees.txt", ";")
{
    m_employeeRecordset.loadFromFile();
}

Employee::~Employee()
{
}

void Employee::addEmployee(std::string args)
{

	system("cls");

    std::vector<std::string> columnAndValues;

    fillArgs(columnAndValues, args);

    if ( columnAndValues.size() == 0 )
    {
        return;
    }

    int position = 0;

    for ( int i = 0 ; i < columnAndValues.size() ; i++ )
    {
        if ( ( position = columnAndValues.at(i).find(":") ) == std::string::npos )
        {
            if ( !m_employeeRecordset.columnExists(columnAndValues.at(i)) )
            {
                std::cout << "Column " << columnAndValues.at(i) << " doesn't exist." << std::endl;
                return;
            }
        }
        else
        {
            if ( !m_employeeRecordset.columnExists(columnAndValues.at(i).substr(0, position)) )
            {
                std::cout << "Column " << columnAndValues.at(i).substr(0, position) << " doesn't exist." << std::endl;
                return;
            }
        }
    }

    m_employeeRecordset.addRow();

    for ( int i = 0 ; i < columnAndValues.size() ; i++ )
    {
        if ( ( position = columnAndValues.at(i).find(":") ) != std::string::npos )
        {
            m_employeeRecordset.fields(columnAndValues.at(i).substr(0, position)) = columnAndValues.at(i).substr(position+1, columnAndValues.at(i).length());
        }
    }

    m_employeeRecordset.writeToFile();

    std::cout << "Employee added" << std::endl;

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

}

void Employee::viewEmployees(std::string args)
{

	system("cls");
    std::vector<std::string> columnNames;

    fillArgs(columnNames, args);

    if ( columnNames.size() == 0 )
    {
        columnNames = m_employeeRecordset.getColumnHeaders();
    }

    for ( int i = 0 ; i < columnNames.size() ; i++ )
    {
        if ( !m_employeeRecordset.columnExists(columnNames.at(i)) )
        {
            std::cout << "Column " << columnNames.at(i) << " doesn't exist." << std::endl;
            return;
        }
    }

    std::cout << "\t|" << std::string ( m_employeeRecordset.getRowLength(columnNames) + columnNames.size() , '*') << "|" << std::endl;

	std::cout << "\t|";

    for ( int i = 0 ; i < columnNames.size() ; i++ )
    {
		if ( i != ( columnNames.size() - 1 ) )
		{
			std::cout << m_employeeRecordset.fields(columnNames.at(i)).getColumnName() << std::string( m_employeeRecordset.fields(columnNames.at(i)).getMaxLength() - m_employeeRecordset.fields(columnNames.at(i)).getColumnName().length(), ' ' ) << "|";
		}
		else
		{
			std::cout << m_employeeRecordset.fields(columnNames.at(i)).getColumnName() << std::string( m_employeeRecordset.fields(columnNames.at(i)).getMaxLength() - m_employeeRecordset.fields(columnNames.at(i)).getColumnName().length(), ' ' ) << " ";
		}
    }

	std::cout << "|";

    std::cout << std::endl << "\t|" << std::string ( m_employeeRecordset.getRowLength(columnNames) + columnNames.size() , '*') << "|" << std::endl;

    m_employeeRecordset.moveFirst();

    while ( m_employeeRecordset.getRow() <= m_employeeRecordset.getRows() )
    {
		std::cout << "\t|";
        for ( int i = 0 ; i < columnNames.size() ; i++ )
        {
			if ( i != ( columnNames.size() - 1 ) )
			{
				std::cout << m_employeeRecordset.fields(columnNames.at(i)) << std::string( m_employeeRecordset.fields(columnNames.at(i)).getMaxLength() - m_employeeRecordset.fields(columnNames.at(i)).getRowText().length(), ' ' ) << "|";
			}
			else
			{
				std::cout << m_employeeRecordset.fields(columnNames.at(i)) << std::string( m_employeeRecordset.fields(columnNames.at(i)).getMaxLength() - m_employeeRecordset.fields(columnNames.at(i)).getRowText().length(), ' ' ) << " ";
			}
        }
        std::cout << "|" << std::endl;
		if ( m_employeeRecordset.getRow() != m_employeeRecordset.getRows() )
		{
			std::cout << "\t|" << std::string ( m_employeeRecordset.getRowLength(columnNames) + columnNames.size() , '-') << "|" << std::endl;
		}

        m_employeeRecordset.moveNext();
    }

	std::cout << "\t|" << std::string ( m_employeeRecordset.getRowLength(columnNames) + columnNames.size() , '*') << "|" << std::endl;

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

void Employee::fillArgs(std::vector<std::string> & vecArgs, std::string args)
{

    int position = 0;

    if ( ( position = args.find(",")) == std::string::npos )
    {
        if ( trim(args).length() != 0 )
        {
            vecArgs.push_back(trim(args));
            args.erase(0, args.length());
        }
    }
    else
    {
        while ( ( position = args.find(",")) != std::string::npos )
        {

            vecArgs.push_back(trim(args.substr(0, position)));
            args.erase(0, position + 1 );
        }
    }

    if ( args.length() > 0 )
    {
        vecArgs.push_back(trim(args));
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

