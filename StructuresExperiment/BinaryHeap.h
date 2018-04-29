#pragma once
#include "TableBase.h"
class BinaryHeap
	:public TableBase
{

public:
	BinaryHeap();
	~BinaryHeap();
	void display(std::ostream & out);
	void pop();
	void push(int val);
	void find(int val);
	void moveDown(int begin);
	void loadFromFile(std::string fileName);
	void moveUp(int sID);
	void populate(int _size);
	std::ostream & operator<<(std::ostream & out);
	void draw(std::ostream & output, int id);
};
