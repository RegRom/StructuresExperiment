#pragma once
class TableBase
{
protected:
	unsigned int size;
	int *content;

public:
	TableBase();
	TableBase(int _size);
	~TableBase();
	virtual void find(int val) = 0;
	void swap(int &a, int &b);
	virtual void loadFromFile(std::string fileName);
	virtual void populate(int size);
	void saveToFile(std::string fileName);
};

