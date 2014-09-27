#include "DataColumn.h"


DataColumn::DataColumn():
	m_name(""), m_next(NULL), m_prev(NULL),
	m_firstRow(NULL), m_lastRow(NULL), m_currentRow(NULL)
{
}

DataColumn::~DataColumn(){
}

void DataColumn::setNext(DataColumn* next){
	m_next = next;
}

DataColumn* DataColumn::getNext(){
	return m_next;
}

void DataColumn::setPrev(DataColumn* prev){
	m_prev = prev;
}

DataColumn* DataColumn::getPrev(){
	return m_prev;
}

void DataColumn::setColumnName(std::string name){
	m_name = name;
}

std::string DataColumn::getColumnName(){
	return m_name;
}

void DataColumn::moveFirst(){
	m_currentRow = m_firstRow;
}

void DataColumn::moveNext(){

	if ( m_currentRow != m_lastRow ){
		m_currentRow = m_currentRow->getNext();
	}

}

void DataColumn::movePrev(){

	if ( m_currentRow != m_firstRow ){
		m_currentRow = m_currentRow->getPrev();
	}

}

void DataColumn::moveLast(){
	m_currentRow = m_lastRow;
}

void DataColumn::addRow(){

	DataRow* newRow = new DataRow;

	if ( m_firstRow == NULL ) {
		newRow->setNext(NULL);
		newRow->setPrev(NULL);

		m_firstRow = newRow;
		m_lastRow = newRow;
	} else {
		newRow->setNext(NULL);
		newRow->setPrev(m_lastRow);

		m_lastRow->setNext(newRow);

		m_lastRow = newRow;
	}

	moveLast();

}

std::string DataColumn::getRowText(){
	return m_currentRow->getText();
}

void DataColumn::operator=(std::string rowText){
	m_currentRow->setText(rowText);
}

std::string DataColumn::operator()(std::string fieldName){
	return m_currentRow->getText();
}

void DataColumn::removeAll(){


	if ( m_firstRow == NULL ) {
		return;
	}

	DataRow* rowToDelete;
	DataRow* currentRow = m_firstRow;

	while ( currentRow->getNext() != NULL ) {

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
