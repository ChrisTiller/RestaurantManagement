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
	DataColumn* getNext() const;

	void setPrev(DataColumn*);
	DataColumn* getPrev() const;

	void setColumnName(std::string);
    std::string getColumnName() const;

	void addRow();
	void removeRow();

	void moveFirst();
	void moveNext();
	void movePrev();
	void moveLast();

	std::string getRowText() const;

	void operator=(std::string);
	bool operator==(std::string);
	bool operator!=(std::string);
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
