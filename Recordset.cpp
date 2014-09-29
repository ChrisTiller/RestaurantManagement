#include "Recordset.h"
#include <iostream>

#include <string>

Recordset::Recordset():
	m_numColumns(0), m_numRows(0), m_firstColumn(NULL),
	m_currentColumn(NULL), m_lastColumn(NULL)
{

}

Recordset::~Recordset(){
	removeAll();
}

void Recordset::addField(std::string columnName){

	DataColumn* newColumn = new DataColumn;

	newColumn->setColumnName(columnName);

	if ( m_firstColumn == NULL ) {

		newColumn->setNext(NULL);
		newColumn->setPrev(NULL);

		m_firstColumn = newColumn;
		m_lastColumn = newColumn;

	} else {

		newColumn->setNext(NULL);
		newColumn->setPrev(m_lastColumn);

		m_lastColumn->setNext(newColumn);

		m_lastColumn = newColumn;

	}

	m_numColumns++;

}

DataColumn Recordset::fields(std::string fieldName){

	DataColumn temp;

	if ( m_firstColumn == NULL ) {
		return temp;
	}

	if ( getRows() == 0 ){
        return temp;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( ( currentCol->getColumnName() != fieldName ) ) {

		currentCol = currentCol->getNext();
		if ( currentCol == NULL ){
			return temp;
		}
	}

	m_currentColumn = currentCol;

	return *(currentCol);

}

void Recordset::moveFirst(){

	if ( m_firstColumn == NULL ) {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL ) {
		currentCol->moveFirst();
		currentCol = currentCol->getNext();
	}
	m_currentRow = 1;
}

void Recordset::moveNext(){

	if ( m_firstColumn == NULL ) {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL ) {
		currentCol->moveNext();
		currentCol = currentCol->getNext();
	}
	m_currentRow++;
}

void Recordset::movePrev(){

	if ( m_firstColumn == NULL ) {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL ) {
		currentCol->movePrev();
		currentCol = currentCol->getNext();
	}
	m_currentRow--;
}

void Recordset::moveLast(){

	if ( m_firstColumn == NULL ) {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL ) {
		currentCol->moveLast();
		currentCol = currentCol->getNext();
	}
	m_currentRow = m_numRows;
}

int Recordset::getColumns(){
	return m_numColumns;
}

int Recordset::getRows(){
	return m_numRows;
}

int Recordset::getRow(){
    return m_currentRow;
}

void Recordset::addRow(){

	if ( m_firstColumn == NULL ) {
		return;
	}

	DataColumn* currentCol = m_firstColumn;

	while ( currentCol != NULL ) {
		currentCol->addRow();
		currentCol = currentCol->getNext();
	}

	m_numRows++;

	moveLast();

}

void Recordset::writeToFile(std::string fileName, std::string delimiter){

	std::ofstream file( fileName.c_str(), std::ios::out | std::ios::trunc );

	if ( !file.fail() ) {

		DataColumn* currentCol = m_firstColumn;

		while ( currentCol != NULL ) {

			file << currentCol->getColumnName() << delimiter;
			currentCol = currentCol->getNext();
		}

		file << '\n';

		moveFirst();

		for ( int i = 1 ; i <= getRows() ; i++ ){

			currentCol = m_firstColumn;

			while ( currentCol != NULL ) {

				file << (*currentCol) << delimiter;
				currentCol = currentCol->getNext();
			}

			file << '\n';

			moveNext();

		}

		file.close();

	}

}

void Recordset::loadFromfile(std::string fileName, std::string delimiter){

	std::ifstream file(fileName.c_str(), std::ios::in);

	if ( !file.fail() ) {

		int lines = 0;
		int cols = 0;
		std::string buffer;


		while ( std::getline(file, buffer, '\n') ) {

			int position = 0;

			if ( lines == 0 ) {

				while ( ( position = buffer.find(delimiter)) != std::string::npos ) {

					addField( buffer.substr( 0, position ) );
					buffer.erase(0, position + delimiter.length() );

					cols++;
				}

			} else {

				addRow();

				DataColumn* currentCol = m_firstColumn;

				while ( ( position = buffer.find(delimiter)) != std::string::npos ) {

					fields(currentCol->getColumnName()) = buffer.substr(0, position);
					buffer.erase(0, position + delimiter.length() );
					currentCol = currentCol->getNext();

				}

			}
			lines++;
		}

		m_numRows = lines - 1;
		m_numColumns = cols;

	}

}


void Recordset::removeAll(){

	if ( m_firstColumn == NULL ) {
		return;
	}

	DataColumn* currentCol = m_firstColumn;
	DataColumn* colToDelete;

	while ( currentCol->getNext() != NULL ) {

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

Recordset Recordset::filter(std::string columnName, std::string filterCriteria){

    Recordset filterRecordset;

    DataColumn* currentCol = m_firstColumn;

    while ( currentCol != NULL ){
        filterRecordset.addField(currentCol->getColumnName());
        currentCol = currentCol->getNext();
    }

    if ( getRows() == 0 ){
        return filterRecordset;
    }

    if ( columnExists(columnName) ) {

        moveFirst();

        while ( getRow() <= getRows() ){

            if (m_currentColumn->getRowText() == filterCriteria ) {

                filterRecordset.addRow();

                currentCol = m_firstColumn;

                while ( currentCol != NULL ){
                    filterRecordset.fields(currentCol->getColumnName()) = currentCol->getRowText();
                    currentCol = currentCol->getNext();
                }
            }
            moveNext();
        }
    }

    return filterRecordset;
}

bool Recordset::columnExists(std::string columnName){

    DataColumn* currentCol = m_firstColumn;

	while ( ( currentCol->getColumnName() != columnName ) ) {

		currentCol = currentCol->getNext();
		if ( currentCol == NULL ){
			return false;
		}
	}

    m_currentColumn = currentCol;

    return true;
}
