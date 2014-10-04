#ifndef RECORDSET_H_INCLUDED
#define RECORDSET_H_INCLUDED

#include "DataColumn.h"
#include "DataRow.h"
#include <string>
#include <fstream>
#include <iostream>

class Recordset
{
public:

	Recordset(std::string="", std::string="");
	~Recordset();

	void addField(std::string);
	DataColumn fields(std::string);
	DataColumn* getFirstColumn() const;

	void moveFirst();
	void moveNext();
	void movePrev();
	void moveLast();

	int getRows() const;
	int getRow() const;
	int getColumns() const;

	void addRow();
	void removeRow();
	void removeAll();
	void update();

	bool isEmpty() const;

	bool columnExists(std::string);

	Recordset filter(std::string, std::string);

	void writeToFile();
	void loadFromFile();


private:
	DataColumn* m_firstColumn;
	DataColumn* m_currentColumn;
	DataColumn* m_lastColumn;

	int m_numRows;
	int m_numColumns;
	int m_currentRow;

	std::string m_fileName;
	std::string m_delimiter;

};

#endif
