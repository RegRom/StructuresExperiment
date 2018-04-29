#pragma once
#include "ListElement.h"
class DoublyLinkedList
{
private:
	ListElement * head, *tail;
	int count;

public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void push_front(int val);
	void push_back(int val);
	void push(int val, ListElement *&p);
	void pop_front();
	void pop_back();
	void remove(ListElement *p);
	ListElement *find(int val);
	void display();
	void loadFromFile(std::string fileName);
	void populate(int _size, int val = 500);
	void saveToFile(std::string fileName);
	void restartList();
	int getCount();
};


