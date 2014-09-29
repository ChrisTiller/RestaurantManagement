#ifndef RECORDSET_H_INCLUDED
#define RECORDSET_H_INCLUDED

#include "DataColumn.h"
#include "DataRow.h"
#include <string>
#include <fstream>
#include <iostream>

class Recordset{

public:

	Recordset();
	~Recordset();

	void addField(std::string);
	DataColumn fields(std::string);

	void moveFirst();
	void moveNext();
	void movePrev();
	void moveLast();

	int getRows();
	int getRow();
	int getColumns();

	void addRow();
	void removeRow();
	void removeAll();

	Recordset filter(std::string, std::string);

	void writeToFile(std::string, std::string);
	void loadFromfile(std::string, std::string);


private:
	DataColumn* m_firstColumn;
	DataColumn* m_currentColumn;
	DataColumn* m_lastColumn;

	int m_numRows;
	int m_numColumns;
	int m_currentRow;

	bool columnExists(std::string);
};

#endif
