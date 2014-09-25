#include "DataRow.h"

DataRow::DataRow():
	m_text(""), m_next(NULL), m_prev(NULL)
{
}

void DataRow::setText(std::string text){
	m_text = text;
}

std::string DataRow::getText(){
	return m_text;
}

void DataRow::setNext(DataRow* next){
	m_next = next;
}

DataRow* DataRow::getNext(){
	return m_next;
}

void DataRow::setPrev(DataRow* prev){
	m_prev = prev;
}

DataRow* DataRow::getPrev(){
	return m_prev;
}