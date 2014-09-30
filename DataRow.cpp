#include "DataRow.h"

DataRow::DataRow():
	m_text(""), m_next(NULL), m_prev(NULL)
{
}

void DataRow::setText(std::string text)
{
	m_text = text;
}

std::string DataRow::getText() const
{
	return m_text;
}

void DataRow::setNext(DataRow* next)
{
	m_next = next;
}

DataRow* DataRow::getNext() const
{
	return m_next;
}

void DataRow::setPrev(DataRow* prev)
{
	m_prev = prev;
}

DataRow* DataRow::getPrev() const
{
	return m_prev;
}
