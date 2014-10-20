#ifndef RECORDSET_H_INCLUDED
#define RECORDSET_H_INCLUDED

#include "DataColumn.h"
#include "DataRow.h"
#include "helperFile.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

struct ColumnRowIntersection
{
    std::string columnName;     // Holds a specific column name
    std::string rowValue;       // Holds a specific row value for the specified columns
};

void fillArgs(std::vector<ColumnRowIntersection>&, std::string);


class Recordset
{
public:

	Recordset(std::string="", std::string="");
	~Recordset();

	void addField(std::string);     // Adds a column to the Recordset
	DataColumn& fields(std::string);// Sets the currentColumn pointer to the column whose name is given in the argument

    // Controls the current row you are looking at in the Recordset
	void moveFirst();
	void moveNext();
	void movePrev();
	void moveLast();
	void moveTo(int);

	int getRows() const;    // Gets the number of rows contained within the Recordset
	int getRow() const;     // Gets the number of the current row you are in within the Recordset
	int getColumns() const; // Gets the number of columns contained within the Recordset
    int getRowLength(std::vector<ColumnRowIntersection>); // Gets the length of the row that would be seen based on the columns given in the argument

    bool containsRow(std::vector<ColumnRowIntersection> cRI); // Determines where the row is that has the specified values, if one exists
    bool containsRow(std::string, std::string); // Determines where the row is that has the specified values, if one exists

    // Controls row addition and deletion within the Recordset
	void addRow(bool=false);
	void removeRow();
	void removeAll();

	bool isEmpty() const; // determines if the Reocrdset doesn't have any rows

	bool columnExists(std::string); // Determines if the column specified exists within the Recordset

	Recordset filter(std::string, std::string);

    // Reads and writes to a specified file
	void write();
	void load();

    // Prints out the Recordset in a grid like form based on the columns that are given to it in the arguments
	void printRecordset(std::string);

    std::vector<ColumnRowIntersection> getColumnHeaders(); // Gets all the column names contained within the Recordset and puts it in a vector

    bool isAutoIncrement();
    void setAutoIncrement(bool);

private:
	DataColumn* m_firstColumn;      // pointer to the first column in the Recordset
	DataColumn* m_currentColumn;    // pointer to the current column in the Recordset
	DataColumn* m_lastColumn;       // pointer to the last column in the Recordset

	int m_numRows;                  // holds the number of rows in the Recordset
	int m_numColumns;               // holds the number of columns in the Reocrdset
	int m_currentRow;               // holds the number of the current row you are in within the Recordset

	std::string m_fileName;         // Holds the filename that the Recordset will read from and write to
	std::string m_delimiter;        // Holds the character that will be used to separate all the information within the output text file
                                    //       as well as what the Recordset looks for in the input file to correctly store the information
    bool m_autoIncrement;
};

#endif
