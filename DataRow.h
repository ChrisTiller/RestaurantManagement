#ifndef DATAROW_H_INCLUDED
#define DATAROW_H_INCLUDED

#include <string>

#define NULL 0

class DataRow{

public:

	DataRow();

	void setText(std::string);
	std::string getText() const;

	void setNext(DataRow*);
	DataRow* getNext() const;

	void setPrev(DataRow*);
	DataRow* getPrev() const;


private:
	DataRow* m_next;
	DataRow* m_prev;

	std::string m_text;
};



#endif