#ifndef RECORDSET_H_INCLUDED
#define RECORDSET_H_INCLUDED

#include "DataColumn.h"
#include "DataRow.h"
#include "File.h"
#include <string>
#include <fstream>
#include <iostream>

class Recordset{

public:

	Recordset();
	~Recordset();

	void addField(std::string);
	DataColumn fields(std::string);
	//std::string fields(int);

	void moveFirst();
	void moveNext();
	void movePrev();
	void moveLast();

	int getRows();
	int getColumns();

	void addRow();

	void writeToFile();
	void loadFromfile(std::string, std::string);

	void removeAll();

private:
	DataColumn* m_firstColumn;
	DataColumn* m_currentColumn;
	DataColumn* m_lastColumn;

	int m_numRows;
	int m_numColumns;

	File m_file;
};

#endif