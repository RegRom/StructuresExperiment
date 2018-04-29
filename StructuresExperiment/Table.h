#pragma once
#include "TableBase.h"
class Table
	:public TableBase
{
private:

public:
	Table();
	Table(int _size);
	~Table();
	void insert_front(int val);
	void insert_back(int val);
	void insert(int val, int id);
	void pop_front();
	void pop_back();
	void remove(int id);
	void display();
	void find(int val);
};