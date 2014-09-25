#ifndef DATACOLUMN_H_INCLUDED
#define DATACOLUMN_H_INCLUDED


#include "DataRow.h"
#include <string>
#include <iostream>

class DataColumn{

public:

	DataColumn();
	~DataColumn();
	
	void setNext(DataColumn*);
	DataColumn* getNext();

	void setPrev(DataColumn*);
	DataColumn* getPrev();

	std::string getColumnName();
	void setColumnName(std::string);

	void addRow();

	void moveFirst();
	void moveNext();
	void movePrev();
	void moveLast();

	std::string getRowText();

	void operator=(std::string);
	std::string operator()(std::string);
	friend std::ostream& operator << (std::ostream&, const DataColumn&);

	void removeAll();

private:
	DataRow* m_firstRow;
	DataRow* m_lastRow;
	DataRow* m_currentRow;

	DataColumn* m_next;
	DataColumn* m_prev;

	std::string m_name;

};


#endif