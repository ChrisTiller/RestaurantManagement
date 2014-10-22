#ifndef DATACOLUMN_H_INCLUDED
#define DATACOLUMN_H_INCLUDED

#include "DataRow.h"
#include <string>
#include <iostream>
#include <math.h>
#include <cassert>

class DataColumn{

public:

	DataColumn();
	~DataColumn();

    //Getters and setters for the next DataColumn in the list
	void setNext(DataColumn*);
	DataColumn* getNext() const;

    // Getters and setters for the previous DataColumn in the list
	void setPrev(DataColumn*);
	DataColumn* getPrev() const;

    // Getters and setters for the name of the DataColumn
	void setColumnName(std::string);
    std::string getColumnName() const;

    // Gets the Text from the current row in the DataColumn
	std::string getRowText() const;

    // DataRow addition and deletion in DataColumn
	void addRow();
	void removeRow();
    void removeAll();

    // Controls the position of the current DataRow in the DataColumn
	void moveFirst();
	void moveNext();
	void movePrev();
	void moveLast();

    // Getters and setters for the length of the longest string in the DataColumn
	void setColWidth(int);
	int getColWidth();
	void recalculateRowLength();


    void operator=(const std::string);
    void operator=(const int);
    void operator=(const double);
    DataColumn& operator=(const DataColumn&);
	bool operator==(std::string);
	bool operator!=(std::string);
	friend std::ostream& operator << (std::ostream&, const DataColumn&);

private:
	DataRow* m_firstRow;    // Holds the pointer to the first row in the DataColumn
	DataRow* m_lastRow;     // Holds the pointer to the last row in the DataColumn
	DataRow* m_currentRow;  // Holds the pointer to the current row in the DataColumn

	DataColumn* m_next;     // Holds the pointer of the next DataColumn
	DataColumn* m_prev;     // Holds the pointer of the previous DataColumn

	std::string m_name;     // Holds the name of the DataColumn
    int m_rowLength;        // Holds the length of the longest string in the DataColumn
};



#endif
