#include "DataColumn.h"


DataColumn::DataColumn():
	m_name(""), m_next(NULL), m_prev(NULL),
	m_firstRow(NULL), m_lastRow(NULL), m_currentRow(NULL)
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
	} else
    {
		newRow->setNext(NULL);
		newRow->setPrev(m_lastRow);

		m_lastRow->setNext(newRow);

		m_lastRow = newRow;
	}

	moveLast();

}

std::string DataColumn::getRowText() const
{
	return m_currentRow->getText();
}

void DataColumn::operator=(const std::string rowText)
{
	m_currentRow->setText(rowText);
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
