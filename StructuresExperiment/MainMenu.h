#pragma once

#include "stdafx.h"
#include "DoublyLinkedList.h"
#include "ListElement.h"
#include "Table.h"
#include "BinaryHeap.h"

class MainMenu
{
private:
	int size;
	std::string greetingMessage;
	std::string tableMenu;
	std::string listMenu;
	std::string heapMenu;
	std::string tableTimeMenu;
	std::string listTimeMenu;
	std::string heapTimeMenu;
	Table *table;
	DoublyLinkedList *list;
	BinaryHeap *heap;
	long double results[101];
	std::chrono::high_resolution_clock::time_point t1, t2;
public:
	MainMenu();
	MainMenu(int _size);
	~MainMenu();
	void setGreetingMessage();
	std::string getGreetingMessage();
	void setTableMenu();
	std::string getTableMenu();
	void setListMenu();
	std::string getListMenu();
	void setHeapMenu();
	std::string getHeapMenu();
	void saveResultsToFile(std::string filePath);
	double saveCountTime();
	void tableExperiments(char option);
	void listExperiments(char option);
	void heapExperiments(char option);
	void setSize(int _size);
	void calcAverage();
	void restartList();
	void restartHeap();
	void tableTimeExperiments(char option);
	void listTimeExperiments(char option);
	void heapTimeExperiments(char option);
	std::string getTableTimeMenu();
	std::string getListTimeMenu();
	std::string getHeapTimeMenu();
	void setTableTimeMenu();
	void setListTimeMenu();
	void setHeapTimeMenu();
	int checkInt(int min, int max);
};

