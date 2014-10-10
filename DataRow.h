#ifndef DATAROW_H_INCLUDED
#define DATAROW_H_INCLUDED

#include <string>

#ifndef NULL
#define NULL 0
#endif // NULL

class DataRow{

public:

	DataRow();

    // Getters and setters for the data contained in the DataRow
	void setText(std::string);
	std::string getText() const;

    // Getters and setters for the next node in the list
	void setNext(DataRow*);
	DataRow* getNext() const;

    // Getters and setters for the previous node in the list
	void setPrev(DataRow*);
	DataRow* getPrev() const;


private:
	DataRow* m_next;    // Holds the pointer to the next DataRow
	DataRow* m_prev;    // Holds the pointer to the previous DataRow

	std::string m_text; // Holds the text that the DataRow will contain
};

#endif
