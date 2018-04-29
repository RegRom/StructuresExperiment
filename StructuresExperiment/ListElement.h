#pragma once
class ListElement
{
private:
	int data;
	ListElement *prev, *next;

public:
	ListElement();
	ListElement(const ListElement &obj);
	~ListElement();
	int getData();
	void setData(int _data);
	void setData(std::string _data);
	void setPrev(ListElement *pv);
	void setNext(ListElement *nx);
	ListElement *getPrev();
	ListElement *getNext();
	void nullifyPrev();
	void nullifyNext();
};