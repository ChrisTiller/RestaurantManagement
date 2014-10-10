#include "Recordset.h"
#include <iostream>
#include <string>



Recordset::Recordset(std::string fileName, std::string delimiter):
	m_numColumns(0), m_numRows(0), m_firstColumn(NULL),
	m_currentColumn(NULL), m_lastColumn(NULL)
{
    m_fileName = fileName;
    m_delimiter = delimiter;
}

Recordset::~Recordset()
{
	removeAll();
}


/*
    parameters:
    description:
*/

void Recordset::addField(std::string columnName)
{

	DataColumn* newColumn = new DataColumn;

	newColumn->setColumnName(columnName);
	newColumn->setColWidth(columnName.length());

	if ( m_firstColumn == NULL )
    {

		newColumn->setNext(NULL);
		newColumn->setPrev(NULL);

		m_firstColumn = newColumn;
		m_lastColumn = newColumn;

	}
	else
    {

		newColumn->setNext(NULL);
		newColumn->setPrev(m_lastColumn);

		m_lastColumn->setNext(newColumn);

		m_lastColumn = newColumn;

	}

	m_numColumns++;

}

DataColumn& Recordset::fields(std::string fieldName)
{

	DataColumn temp;

	if ( m_firstColumn == NULL )
    {
		return temp;
	}

	//if ( getRows() == 0 )
    //{
    //    return temp;
	//}

	DataColumn* currentCol = m_firstColumn;

	while ( ( currentCol->getColumnName() != fieldName ) )
    {

		currentCol = currentCol->getNext();
		if ( currentCol == NULL )
        {
			return temp;
		}
	}

	m_currentColumn = currentCol;

	return *(m_currentColumn);

}

void Recordset::moveFirst()
{

	if ( m_firstColumn == NULL )
    {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL )
    {
		currentCol->moveFirst();
		currentCol = currentCol->getNext();
	}
	m_currentRow = 1;
}

void Recordset::moveNext()
{

	if ( m_firstColumn == NULL )
    {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL )
    {
		currentCol->moveNext();
		currentCol = currentCol->getNext();
	}
	m_currentRow++;
}

void Recordset::movePrev()
{

	if ( m_firstColumn == NULL )
    {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL )
    {
		currentCol->movePrev();
		currentCol = currentCol->getNext();
	}
	m_currentRow--;
}

void Recordset::moveLast()
{

	if ( m_firstColumn == NULL )
    {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL )
    {
		currentCol->moveLast();
		currentCol = currentCol->getNext();
	}
	m_currentRow = m_numRows;
}

int Recordset::getColumns() const
{
	return m_numColumns;
}

int Recordset::getRows() const
{
	return m_numRows;
}

int Recordset::getRow() const
{
    return m_currentRow;
}

void Recordset::addRow()
{

	if ( m_firstColumn == NULL )
    {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL )
    {
		currentCol->addRow();
		currentCol = currentCol->getNext();
	}

	m_numRows++;

}

void Recordset::write()
{

	std::ofstream file( m_fileName.c_str(), std::ios::out | std::ios::trunc );

	if ( !file.fail() )
    {

		DataColumn* currentCol = m_firstColumn;

		while ( currentCol != NULL )
        {

			file << currentCol->getColumnName() << m_delimiter;
			currentCol = currentCol->getNext();
		}

		file << '\n';

		moveFirst();

		for ( int i = 1 ; i <= getRows() ; i++ )
        {

			currentCol = m_firstColumn;

			while ( currentCol != NULL )
            {
				file << (*currentCol) << m_delimiter;
				currentCol = currentCol->getNext();
			}

			file << '\n';

			moveNext();
		}
		file.close();
	}
}

void Recordset::load()
{

	std::ifstream file(m_fileName.c_str(), std::ios::in);

	if ( !file.fail() )
    {
		int lines = 0;
		int cols = 0;
		std::string buffer;

		while ( std::getline(file, buffer, '\n') )
        {

			int position = 0;

			if ( lines == 0 )
            {

				while ( ( position = buffer.find(m_delimiter)) != std::string::npos )
                {

					addField( buffer.substr( 0, position ) );
					buffer.erase(0, position + m_delimiter.length() );

					cols++;
				}

			}
			else
            {

				addRow();

				DataColumn* currentCol = m_firstColumn;

				while ( ( position = buffer.find(m_delimiter)) != std::string::npos )
                {

					fields(currentCol->getColumnName()) = buffer.substr(0, position);
					buffer.erase(0, position + m_delimiter.length() );
					currentCol = currentCol->getNext();

				}

			}
			lines++;
		}
		m_numRows = lines - 1;
		m_numColumns = cols;
	}
}


void Recordset::removeAll()
{

	if ( m_firstColumn == NULL )
    {
		return;
	}

	DataColumn* currentCol = m_firstColumn;
	DataColumn* colToDelete;

	while ( currentCol->getNext() != NULL )
    {

		colToDelete = currentCol;

		currentCol = currentCol->getNext();

		colToDelete->removeAll();
		colToDelete->setNext(NULL);
		colToDelete->setPrev(NULL);
		colToDelete->setColumnName("");

		delete colToDelete;

	}

	m_firstColumn = NULL;
	m_lastColumn = NULL;
	m_currentColumn = NULL;

	m_numColumns = 0;
	m_numRows = 0;

}

Recordset Recordset::filter(std::string columnName, std::string filterCriteria)
{

    Recordset filterRecordset;

    DataColumn* currentCol = m_firstColumn;

    while ( currentCol != NULL )
    {
        filterRecordset.addField(currentCol->getColumnName());
        currentCol = currentCol->getNext();
    }

    if ( getRows() == 0 )
    {
        return filterRecordset;
    }

    if ( columnExists(columnName) )
    {

        moveFirst();

        while ( getRow() <= getRows() )
        {

            if (m_currentColumn->getRowText() == filterCriteria )
            {

                filterRecordset.addRow();

                currentCol = m_firstColumn;

                while ( currentCol != NULL )
                {
                    filterRecordset.fields(currentCol->getColumnName()) = currentCol->getRowText();
                    currentCol = currentCol->getNext();
                }
            }
            moveNext();
        }
    }

    return filterRecordset;
}

bool Recordset::columnExists(std::string columnName)
{
    DataColumn* currentCol = m_firstColumn;

	while ( ( currentCol->getColumnName() != columnName ) )
    {

		currentCol = currentCol->getNext();
		if ( currentCol == NULL )
        {
			return false;
		}
	}

    m_currentColumn = currentCol;

    return true;
}

void Recordset::removeRow()
{
    if ( m_numRows > 0 )
    {

        DataColumn* currentCol = m_firstColumn;

        int rowLength = 0;

        while ( currentCol != NULL )
        {
            rowLength = currentCol->getColWidth();
            currentCol->removeRow();

            if ( rowLength == currentCol->getColWidth() )
            {
                currentCol->recalculateRowLength();
            }

            currentCol = currentCol->getNext();
        }

        m_numRows--;
    }
}

bool Recordset::isEmpty() const
{
    bool result = false;

    if ( m_numRows == 0 )
    {
        result = true;
    }

    return result;
}

void Recordset::moveTo(int row)
{

    if ( (row > m_numRows) || ( row == m_currentRow ) || ( row <= 0 ) )
    {
        return;
    }

    int fromBeginning = row - 1;
    int fromEnd = m_numRows - row;
    int fromCurrent = m_currentRow - row;
    int fromCurrentAbs = std::abs(fromCurrent);

    if ( fromBeginning <= fromCurrentAbs )
    {
        if ( fromBeginning <= fromEnd )
        {
            moveFirst();
            for ( int i = 1 ; i < row ; i++)
            {
                moveNext();
            }
            return;
        }
    }
    if ( fromCurrentAbs <= fromBeginning )
    {
        if ( fromCurrentAbs <= fromEnd )
        {
            if ( fromCurrentAbs == fromCurrent )
            {
                for ( int i = m_currentRow ; i > row ; i--)
                {
                    movePrev();
                }
                return;
            }
            else
            {
                for ( int i = m_currentRow ; i < row ; i++)
                {
                    moveNext();
                }
                return;
            }
        }
    }
    if ( fromEnd <= fromBeginning )
    {
        if ( fromEnd <= fromCurrentAbs )
        {
            moveLast();
            for ( int i = m_numRows ; i > row ; i--)
            {
                movePrev();
            }
            return;
        }
    }
}

std::vector<ColumnRowIntersection> Recordset::getColumnHeaders()
{

    std::vector<ColumnRowIntersection> cols;
    ColumnRowIntersection cRI;

    if ( m_firstColumn == NULL )
    {
        return cols;
    }

    DataColumn* currenctCol = m_firstColumn;

    while ( currenctCol != NULL )
    {
        cRI.columnName = currenctCol->getColumnName();
        cRI.rowValue = "";
        cols.push_back(cRI);
        currenctCol = currenctCol->getNext();
    }

    return cols;

}

int Recordset::getRowLength(std::vector<ColumnRowIntersection> columns)
{

    if ( m_firstColumn == NULL )
    {
        return 0;
    }

    int length = 0;

    for ( int i = 0 ; i < columns.size() ; i++ )
	{
		length += fields(columns.at(i).columnName).getColWidth();
	}
    return length;
}

void Recordset::printRecordset(std::string args)
{

    std::vector<ColumnRowIntersection> cRI;

    fillArgs(cRI, args);

    if ( cRI.size() == 0 )
    {
        cRI = getColumnHeaders();
    }

    std::string message = "Recordset is empty";

    int rowLength = getRowLength(cRI) + cRI.size();
    int padding = 0;
    int totalWidth = 0;

    if ( message.length() >= rowLength )
    {
        rowLength += 2;
    }

    // prints out the top border
    std::cout << "\t|" << std::string ( rowLength , '*') << "|" << std::endl;

	std::cout << "\t|";

    for ( int i = 0 ; i < cRI.size() ; i++ )
    {
        padding = (fields(cRI.at(i).columnName).getColWidth() - cRI.at(i).columnName.length())/2;
        totalWidth = fields(cRI.at(i).columnName).getColWidth();

        // Prints out the columns and centers them
        std::cout << std::string( padding, ' ' ) << cRI.at(i).columnName << std::string( totalWidth - (padding + cRI.at(i).columnName.length()), ' ' );


        // depending on the column your on, it will print a " " signifying your at the end of the columns
		if ( i != ( cRI.size() - 1 ) )
		{
			 std::cout << "|";
		}
		else
		{
			std::cout << " ";
		}
    }

	std::cout << "|";

    std::cout << std::endl << "\t|" << std::string ( getRowLength(cRI) + cRI.size() , '*') << "|" << std::endl;

    if ( getRows() != 0 )
    {
        moveFirst();

        while ( getRow() <= getRows() )
        {
            std::cout << "\t|";
            for ( int i = 0 ; i < cRI.size() ; i++ )
            {
                // Prints out the current row information
                std::cout << fields(cRI.at(i).columnName) << std::string( fields(cRI.at(i).columnName).getColWidth() - fields(cRI.at(i).columnName).getRowText().length(), ' ' );
                // Depending on the column your on, it will print a "|" or " ", with the " " signifying your at the end of the row
                if ( i != ( cRI.size() - 1 ) )
                {
                    std::cout << "|";
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << "|" << std::endl;
            if ( getRow() != getRows() )
            {
                // Prints out the row separator
                std::cout << "\t|" << std::string ( getRowLength(cRI) + cRI.size() , '-') << "|" << std::endl;
            }

            moveNext();
        }
    }
    else
    {
        // Prints out a message saying the reordset is empty if the recordset is empty
        padding = ((getRowLength(cRI) + cRI.size() ) - message.length())/2;
        totalWidth = getRowLength(cRI) + cRI.size()-1;
        std::cout << "\t|" << std::string ( padding, ' ') << message << std::string( totalWidth - (padding+ message.length()), ' ') << "|" << std::endl;
    }

	std::cout << "\t|" << std::string ( getRowLength(cRI) + cRI.size() , '*') << "|" << std::endl;

}

// fills a vector that is passed in with a column name and row value with the given argument
void fillArgs(std::vector<ColumnRowIntersection>& vecArgs, std::string args)
{
    int commaPosition = 0;
    int colonPosition = 0;
    ColumnRowIntersection cRI;

    args = trim(args);

    // Looks for a comma. This separates the different column names and row values
    // Example: args = "First Name:Lonnie, Last Name:Bowe"
    // This will split it into "First Name:Lonnie" and "Last Name:Bowe"
    // Then it is split by the ":" to separate column names with their respective row values
    // Example: "First Name:Lonnie" becomes
    // column name = "First Name"
    // row value = "Lonnie"
    // It then pushes onto a vector a structure that contains variables to hold the values to retrieve them easier later on
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

    // If there is just one column and row value given then this piece of code will execute to do the same exact thing
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

// Returns a trimmed string so that there are no beginning or ending spaces
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
