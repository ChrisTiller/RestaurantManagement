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

	if ( m_currentRow != m_lastRow )
    {
		m_currentRow = m_currentRow->getNext();
	}

}

void DataColumn::movePrev()
{

	if ( m_currentRow != m_firstRow )
    {
		m_currentRow = m_currentRow->getPrev();
	}

}

void DataColumn::moveLast()
{
	m_currentRow = m_lastRow;
}

void DataColumn::addRow()
{

	DataRow* newRow = new DataRow;

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

	m_currentRow = m_lastRow;

}

std::string DataColumn::getRowText() const
{
	return m_currentRow->getText();
}

void DataColumn::operator=(const std::string rowText)
{
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

    if ( m_firstRow == NULL )
    {
        return;
    }

    DataRow* row;

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
    //std::stringstream ss;
    //ss << rhs;
    //m_currentRow->setText(ss.str());

    int length = 0;
    std::string invertedValue = "";
    std::string value = "";

    while ( ( rhs/(int)pow(10, length)) > 0)
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
