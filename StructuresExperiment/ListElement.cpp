#include "stdafx.h"
#include "ListElement.h"


ListElement::ListElement()
{
	this->data = 0;
	this->prev = nullptr;
	this->next = nullptr;
}

ListElement::ListElement(const ListElement & obj)
{
	data = obj.data;
	prev = new ListElement;
	next = new ListElement;
	*prev = *obj.prev;
	*next = *obj.next;
}


ListElement::~ListElement()
{
}

int ListElement::getData()
{
	return this->data;
}

void ListElement::setData(int _data)
{
	this->data = _data;
}

void ListElement::setData(std::string _data)
{
	this->data = std::stoi(_data);
}

void ListElement::setPrev(ListElement * pv)
{
	this->prev = new ListElement;
	prev = pv;
}

void ListElement::setNext(ListElement * nx)
{
	this->next = new ListElement;
	next = nx;
}

ListElement * ListElement::getPrev()
{
	return this->prev;
}

ListElement * ListElement::getNext()
{
	return this->next;
}

void ListElement::nullifyPrev()
{
	delete prev;
	prev = nullptr;
}

void ListElement::nullifyNext()
{
	delete next;
	next = nullptr;
}