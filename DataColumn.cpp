#include "DataColumn.h"
#include <math.h>

DataColumn::DataColumn():
	m_name(""), m_next(NULL), m_prev(NULL),
	m_firstRow(NULL), m_lastRow(NULL), m_currentRow(NULL),
	m_rowLength(0)
{
}

DataColumn::~DataColumn()
{
}

void DataColumn::setNext(DataColumn* next)
{
	m_next = next;
}

DataColumn* DataColumn::getNext() const
{
	return m_next;
}

void DataColumn::setPrev(DataColumn* prev)
{
	m_prev = prev;
}

DataColumn* DataColumn::getPrev() const
{
	return m_prev;
}

void DataColumn::setColumnName(std::string name)
{
	m_name = name;
}

std::string DataColumn::getColumnName() const
{
	return m_name;
}

void DataColumn::moveFirst()
{
	m_currentRow = m_firstRow;
}

void DataColumn::moveNext()
{
    // Moves the currentRow pointer to the next DataRow in the DataColumn
    // provided the row isn't already the last row
	if ( m_currentRow != m_lastRow )
    {
		m_currentRow = m_currentRow->getNext();
	}
}

void DataColumn::movePrev()
{
    // Moves the currentRow pointer to the previous DataRow in the DataColumn
    // provided the row isn't already the first row
	if ( m_currentRow != m_firstRow )
    {
		m_currentRow = m_currentRow->getPrev();
	}
}

void DataColumn::moveLast()
{
    // Moves the currentRow pointer to the last DataRow in the DataColumn
	m_currentRow = m_lastRow;
}

void DataColumn::addRow()
{
    // Creates a pointer to a new DataRow and adds it to the end of the DataColumn
	DataRow* newRow = new DataRow;

    // If firstRow is NULL, list is empty so we need to make the firstRow
    // Else append the new DataRow to the end of the DataColumn
	if ( m_firstRow == NULL )
    {
		newRow->setNext(NULL);
		newRow->setPrev(NULL);

		m_firstRow = newRow;
		m_lastRow = newRow;
	}
	else
    {
		newRow->setNext(NULL);
		newRow->setPrev(m_lastRow);

		m_lastRow->setNext(newRow);

		m_lastRow = newRow;
	}

    // Sets the currentRow pointer to the newly created DataRow for editing purposes later on
	m_currentRow = m_lastRow;

}

std::string DataColumn::getRowText() const
{
	return m_currentRow->getText();
}

void DataColumn::operator=(const std::string rowText)
{
    // Sets the currentRow's text value and checks if it's length
    // is greater than the last known greatest length in the DataColumn
    // for later alignment
	m_currentRow->setText(rowText);

	if ( rowText.length() > m_rowLength )
    {
        m_rowLength = rowText.length();
    }
}

DataColumn& DataColumn::operator=(const DataColumn& dt)
{
    m_currentRow->setText(dt.getRowText());

    return *this;
}

void DataColumn::removeAll()
{
    // Removes all the rows within the DataColumn
	if ( m_firstRow == NULL )
    {
		return;
	}

	DataRow* rowToDelete;
	DataRow* currentRow = m_firstRow;

	while ( currentRow->getNext() != NULL )
    {

		rowToDelete = currentRow;

		currentRow = currentRow->getNext();

		rowToDelete->setPrev(NULL);
		rowToDelete->setNext(NULL);
		rowToDelete->setText("");

		delete rowToDelete;

	}

	m_firstRow = NULL;
	m_lastRow = NULL;
	m_currentRow = NULL;

}

std::ostream& operator << (std::ostream& osObject, const DataColumn& dt)
{
	osObject << dt.m_currentRow->getText();

	return osObject;
}

void DataColumn::removeRow()
{
    // Removes the current DataRow from the DataColumn and the
    // currentRow pointer will be set to the DataRow after the DataRow you are deleting
    if ( m_firstRow == NULL )
    {
        return;
    }

    DataRow* row;

    // deals with the case if you only have one row in your DataColumn list
    if ( m_firstRow == m_lastRow )
    {

        row = m_firstRow;
        row->setNext(NULL);
        row->setPrev(NULL);
        row->setText("");

        delete row;

        m_firstRow = NULL;
        m_lastRow = NULL;
        m_currentRow = NULL;

        return;

    }

    // deals with if the row up for deletion is the first row or the last row in the DataColumn list
    if ( m_currentRow == m_firstRow )
    {
        row = m_firstRow;

        m_firstRow = m_firstRow->getNext();

        row->setNext(NULL);
        row->setPrev(NULL);
        row->setText("");

        m_firstRow->setPrev(NULL);

        m_currentRow = m_firstRow;

        return;
    }
    else if ( m_currentRow == m_lastRow )
    {

        row = m_lastRow;

        m_lastRow = m_lastRow->getPrev();

        m_lastRow->setNext(NULL);

        row->setNext(NULL);
        row->setPrev(NULL);
        row->setText("");

        m_currentRow = m_lastRow;

        delete row;

        return;
    }

    // deals with a random DataRow in the DataColumn up for deletion
    row = m_currentRow;

    m_currentRow->getPrev()->setNext(m_currentRow->getNext());
    m_currentRow->getNext()->setPrev(m_currentRow->getPrev());

    row->setPrev(NULL);
    row->setNext(NULL);
    row->setText("");

    m_currentRow = m_currentRow->getNext();

    delete row;

}

bool DataColumn::operator==(std::string value)
{
    if ( m_currentRow->getText() == value )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DataColumn::operator!=(std::string value)
{
    return !operator==(value);
}

void DataColumn::operator=(const int rhs)
{
    // converts a given integer into a string and stores it in the current DataRow in the DataColumn

    int length = 0;
    std::string invertedValue = "";
    std::string value = "";

    if ( rhs == 0 )
    {
        m_currentRow->setText("0");
    }

    while ( ( rhs / (int)pow(10, length) ) > 0 )
    {
        length++;
    }

    length--;
    int currentvalue = rhs;
    int numberToCompare = 0;

    while ( length >= 0)
    {
        numberToCompare = currentvalue%10;

        switch ( numberToCompare )
        {
        case 0:
            {
                invertedValue += "0";
                break;
            }
        case 1:
            {
                invertedValue += "1";
                break;
            }
        case 2:
            {
                invertedValue += "2";
                break;
            }
        case 3:
            {
                invertedValue += "3";
                break;
            }
        case 4:
            {
                invertedValue += "4";
                break;
            }
        case 5:
            {
                invertedValue += "5";
                break;
            }
        case 6:
            {
                invertedValue += "6";
                break;
            }
        case 7:
            {
                invertedValue += "7";
                break;
            }
        case 8:
            {
                invertedValue += "8";
                break;
            }
        case 9:
            {
                invertedValue += "9";
                break;
            }
        }

        currentvalue = currentvalue/10;
        length--;
    }

    // string value of the integer is reversed so we need to get the
    // original value back
    for ( int i = invertedValue.length() - 1 ; i >= 0 ; i-- )
    {
        value += invertedValue[i];
    }

    m_currentRow->setText(value);

}

void DataColumn::operator=(const double rhs)
{
    int length = 0;
    std::string invertedValue = "";
    std::string value = "";

    while ( ( rhs/(int)pow(10, length)) > 0)
    {
        length++;
    }

    length--;
    double currentvalue = rhs;
    int numberToCompare = 0;

    while ( length >= 0)
    {
        numberToCompare = fmod(currentvalue,10);

        switch ( numberToCompare )
        {
        case 0:
            {
                invertedValue += "0";
                break;
            }
        case 1:
            {
                invertedValue += "1";
                break;
            }
        case 2:
            {
                invertedValue += "2";
                break;
            }
        case 3:
            {
                invertedValue += "3";
                break;
            }
        case 4:
            {
                invertedValue += "4";
                break;
            }
        case 5:
            {
                invertedValue += "5";
                break;
            }
        case 6:
            {
                invertedValue += "6";
                break;
            }
        case 7:
            {
                invertedValue += "7";
                break;
            }
        case 8:
            {
                invertedValue += "8";
                break;
            }
        case 9:
            {
                invertedValue += "9";
                break;
            }
        }

        currentvalue = currentvalue/10;
        length--;
    }

    for ( int i = invertedValue.length() - 1 ; i >= 0 ; i-- )
    {
        value += invertedValue[i];
    }

    m_currentRow->setText(value);
}

void DataColumn::setColWidth(int length)
{
    m_rowLength = length;
}

int DataColumn::getColWidth()
{
    return m_rowLength;
}

void DataColumn::recalculateRowLength()
{
    // Goes through the DataRow list in the DataColumn to determine
    // what the longest string in the DataColumn is
    m_rowLength = m_name.length();

    DataRow* currentRow = m_firstRow;

    while ( currentRow != NULL )
    {
        if ( currentRow->getText().length() > m_rowLength )
        {
            m_rowLength = currentRow->getText().length();
        }
        currentRow = currentRow->getNext();
    }

}
