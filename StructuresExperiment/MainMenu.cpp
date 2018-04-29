#include "stdafx.h"
#include "MainMenu.h"

//Konstruktor domy�lny
MainMenu::MainMenu()
{
	setGreetingMessage();
	setTableMenu();
	setListMenu();
	setHeapMenu();
	setTableTimeMenu();
	setListTimeMenu();
	setHeapTimeMenu();
	this->table = new Table(1000);
	this->list = new DoublyLinkedList();
	this->heap = new BinaryHeap();
}

//Konstruktor do tworzenia struktur o zadanym rozmiarze
MainMenu::MainMenu(int _size)
{
	setGreetingMessage();
	setTableMenu();
	setListMenu();
	setHeapMenu();
	setTableTimeMenu();
	setListTimeMenu();
	setHeapTimeMenu();
	this->size = _size;
	this->table = new Table(size);
	this->list = new DoublyLinkedList();
	this->heap = new BinaryHeap();
}


MainMenu::~MainMenu()
{
	delete table;
	delete list;
	delete heap;
}

//Metoda ustawiaj�ca tekst g��wnego menu
void MainMenu::setGreetingMessage()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a nast�pnie pobieramy je do jednego stringa
	ss << "\n[1] Test an array\n" << "[2] Test a doubly linked list\n" << "[3] Test a binary heap\n";
	ss << "[4] Measure time of array operations\n" << "[5] Measure time of list operations\n" << "[6] Measure time of heap operations\n";
	ss << "[7] Change the size of structures\n" << "[0] Exit the program\n" << "\nYour choice: ";
	this->greetingMessage = ss.str();
}

//Metoda zwracaj�ca tekst g��wnego menu
std::string MainMenu::getGreetingMessage()
{
	return this->greetingMessage;
}

//Metoda ustawiaj�ca tekst menu tablicy
void MainMenu::setTableMenu()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a nast�pnie pobieramy je do jednego stringa
	ss << "Array measurements:\n";
	ss << "[1] Load array from file\n" << "[2] Fill the array with random numbers\n" << "[3] Search in an array\n";
	ss << "[4] Add element in front\n" << "[5] Add element in the middle\n";
	ss << "[6] Add element at the end\n" << "[7] Delete in the front\n";
	ss << "[8] Delete in the middle\n" << "[9] Delete at the end\n";
	ss << "[0] Show contents of the table\n" << "[q] Return to main menu\n" << "\nYour choice: ";
	this->tableMenu = ss.str();
}

//Metoda pobieraj�ca tekst menu tablicy
std::string MainMenu::getTableMenu()
{
	return this->tableMenu;
}

//Metoda ustawiaj�ca tekst menu listy
void MainMenu::setListMenu()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a nast�pnie pobieramy je do jednego stringa
	ss << "Doubly linked list measurements:\n";
	ss << "[1] Load the list from file\n" << "[2] Fill the list with random numbers\n" << "[3] Measure the time of searching\n";
	ss << "[4] Add element in front\n" << "[5] Add element in the middle\n";
	ss << "[6] Add element at the end\n" << "[7] Delete in the front\n";
	ss << "[8] Delete in the middle\n" << "[9] Delete at the end\n";
	ss << "[0] Show contents of the list\n" << "[q] Return to main menu\n" << "\nYour choice: ";
	this->listMenu = ss.str();
}

//Metoda pobieraj�ca tekst menu listy
std::string MainMenu::getListMenu()
{
	return this->listMenu;
}

//Metoda ustawiaj�ca tekst menu kopca
void MainMenu::setHeapMenu()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a nast�pnie pobieramy je do jednego stringa
	ss << "Binary heap measurements:\n";
	ss << "[1] Load the heap from file\n" << "[2] Fill the heap with random numbers\n" << "[3] Search in the heap\n";
	ss << "[4] Add an element\n" << "[5] Remove the root\n";
	ss << "[0] Show contents of the heap\n" << "[q] Return to main menu\n" << "\nYour choice: ";
	this->heapMenu = ss.str();
}

//Metoda ustawiaj�ca tekst menu kopca
std::string MainMenu::getHeapMenu()
{
	return heapMenu;
}

//Metoda zapisuj�ca wyniki pomiar�w do pliku
void MainMenu::saveResultsToFile(std::string filePath)
{
	std::fstream file;						//tworzymy zmienn� plikow�
	file.open(filePath, std::ios::out);		//otwieramy do zapisu
	if (file.good()) {						//sprawdzamy czy plik nie jest uszkodzony
		for (int i = 0; i < 101; i++)
		{
			file << std::fixed;										//wy��czamy notacj� naukow�
			file << std::setprecision(8) << results[i] << "\n";		//ustawiamy ilosc miejsc po przecinku w wyniku i zapisujemy wynik
		}
		file.close();
	}
}

//Metoda zapisuj�ca czas wykonania operacji na strukturze
double MainMenu::saveCountTime()
{
	namespace clk = std::chrono;		//tworzenie aliasu dla przestrzeni nazw
	clk::high_resolution_clock::rep time = clk::duration_cast<clk::nanoseconds>(t2 - t1).count();		//obliczamy czas wykonania odejmuj�c czas pocz�tkowy od koncowego
	long double expTime = (long double)time * pow(10, -9);												//konwertujemy wynik w nanosekundach do sekund
	return expTime;
}

//#################################################################
//#################### EKSPERYMENTY NA TABLICY ####################
//#################################################################

void MainMenu::tableExperiments(char option)
{
	int val;
	switch (option)
	{
	case '1':
		table->loadFromFile("table.txt");										//wczytywanie tablicy z pliku
		break;
	case '2':
	{
		table->populate(size);													//zape�niamy tablic� o rozmiarze size losowymi elementami
		std::cout << "The table has been populated with random numbers\n";
		getchar();
	}
	break;
	case '3':
	{
		std::cout << "Input a value you wish to find: ";
		val = checkInt(1, 20000);

		table->find(val);
		getchar();
	}
	break;
	case '4':
	{
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);

		table->insert_front(val);
	}
	break;
	case '5':
	{
		int id;
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		std::cout << "Input a index: ";
		id = checkInt(0, size - 1);

		table->insert(val, id);												//Umieszczamy wprowadzon� warto�� na wygenerowanym indeksie
	}
	break;
	case '6':
	{
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);

		table->insert_back(val);											//Umieszczamy warto�� na ko�cu tablicy
	}
	break;
	case '7':
	{
		table->pop_front();													//Usuwamy warto�� z pocz�tku
	}
	break;
	case '8':
	{
		int id;
		std::cout << "Input a index: ";
		id = checkInt(1, size - 2);
		table->remove(id);													//Usuwamy warto�� na losowo wygenerowanym indeksie
	}
	break;
	case '9':
	{
		table->pop_back();													//Usuwamy warto�� z ko�ca tablicy
	}
	break;
	case '0':
	{
		table->display();														//Wy�wietlamy warto�ci tablicy
		getchar();
	}
	break;
	case 'q':
		return;
	default:
		std::cout << "An unidentified option has been chosen, please input correct parameter to perfom an action!\n";
	}
}

//################################################################
//#################### EKSPERYMENTY NA LI�CIE ####################
//################################################################

void MainMenu::listExperiments(char option)
{
	int val;
	switch (option)
	{
	case '1':
		list->loadFromFile("list.txt");
		break;
	case '2':
	{
		this->restartList();												//Zerujemy list�, aby dodawa� elementy od zera
		list->populate(size);												//Zape�niamy list� losowymi liczbami
		std::cout << "The list has been populated with random numbers\n";
		getchar();
	}
	break;
	case '3':
	{
		std::cout << "Input a value you wish to find: ";
		val = checkInt(1, 20000);

		ListElement *el;												//Tworzymy nowy wska�nik
		el = list->find(val);											//Ustawiamy stworzony wska�nik na wyszukan� warto��
		getchar();
	}
	break;
	case '4':
	{
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);

		list->push_front(val);											//Dodajemy element na pocz�tku listy
	}
	break;
	case '5':
	{
		int succ;
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		std::cout << "Choose successor: ";
		succ = checkInt(1, 20000);

		ListElement *el = list->find(succ);								//Tworzymy nowy wska�nik i ustawiamy go na wyszukan� warto�� nast�pnika
		list->push(val, el);
	}
	break;
	case '6':
	{
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);

		list->push_back(val);											//Dodajemy element na ko�cu listy
	}
	break;
	case '7':
	{
		list->pop_front();												//Usuwamy element z pocz�tku listy
	}
	break;
	case '8':
	{
		std::cout << "Input a value you wish to remove: ";
		val = checkInt(1, 20000);

		ListElement *el;
		el = list->find(val);
		if (!el)
		{
			getchar();
			break;
		}
		list->remove(el);
	}
	break;
	case '9':
	{
		list->pop_back();
	}
	break;
	case '0':
	{
		int lcount = list->getCount();
		if (lcount > 0)
		{
			list->display();
			getchar();
		}
		else
		{
			std::cout << "The list is empty\n";
			getchar();
		}
		break;
	}
	case 'q':
		return;
	default:
		std::cout << "An unidentified option has been chosen, please input correct parameter to perfom an action!\n";
	}
}

//################################################################
//#################### EKSPERYMENTY NA KOPCU #####################
//################################################################

void MainMenu::heapExperiments(char option)
{
	int val;
	switch (option)
	{
	case '1':
		this->restartHeap();
		heap->loadFromFile("heap.txt");
		break;
	case '2':
	{
		this->restartHeap();
		heap->populate(size);
		std::cout << "The heap has been populated with random numbers\n";
		getchar();
	}
	break;
	case '3':
	{
		std::cout << "Input a value you wish to find: ";
		val = checkInt(1, 20000);

		heap->find(val);
		getchar();
	}
	break;
	case '4':
	{
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);

		heap->push(val);
	}
	break;
	case '5':
	{
		heap->pop();
	}
	break;
	case '0':
	{
		heap->display(std::cout);
		getchar();
	}
	break;
	case 'q':
		return;
	default:
		std::cout << "An unidentified option has been chosen, please input correct parameter to perfom an action!\n";
	}
}

//Setter ustawiaj�cy rozmiar dla struktur
void MainMenu::setSize(int _size)
{
	this->size = _size;
}

//Metoda obliczaj�ca warto�� �redni� czasu wykonania
void MainMenu::calcAverage()
{
	long double sum = 0;
	long double avg = 0;
	for (int i = 0; i < 100; i++)
	{
		sum += results[i];
	}
	avg = sum / 100;
	results[100] = avg;
}

//Metoda zeruj�ca list� i tworz�ca now�, pust�
void MainMenu::restartList()
{
	delete list;
	list = nullptr;
	list = new DoublyLinkedList();
}

//Metoda zeruj�ca kopiec i tworz�ca nowy, pusty
void MainMenu::restartHeap()
{
	delete heap;
	heap = nullptr;
	heap = new BinaryHeap();
}

void MainMenu::tableTimeExperiments(char option)
{
	int val;
	switch (option)
	{
	case '1':
		table->loadFromFile("table.txt");										//wczytywanie tablicy z pliku
		break;
	case '2':
		table->populate(size);													//zape�niamy tablic� o rozmiarze size losowymi elementami
		std::cout << "The table has been populated with random numbers\n";
		getchar();
		break;
	case '3':
		std::cout << "Input a value you wish to find: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)									//operacj� powtarzamy 100 razy
		{
			table->populate(size);
			t1 = std::chrono::high_resolution_clock::now();						//Pobieramy warto�� czasu bezpo�rednio przed wykonaniem operacji
			table->find(val);													//wyszukujemy element w p�tli
			t2 = std::chrono::high_resolution_clock::now();						//Pobieramy warto�� czasu bezpo�rednio przed wykonaniem operacji
			results[i] = saveCountTime();										//Obliczamy czas trwania operacji i zapisujemy wynik
		}
		calcAverage();															//Obliczamy warto�� �redni� czasu wykonywania operacji i zapisujemy
		saveResultsToFile("TableSearch.txt");									//Zapisujemy tablic� do pliku
		break;
	case '4':
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			table->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			table->insert_front(val);											//Dodajemy warto�� na pocz�tku tablicy
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("TableFrontAdding.txt");
		break;
	case '5':
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			table->populate(size);
			srand(time(NULL));													//Uruchamiamy generator liczb pseudolosowych
			int id = rand() % (size - 1) + 1;										//Generujemy pseudoloswy indeks
			t1 = std::chrono::high_resolution_clock::now();
			table->insert(val, id);												//Umieszczamy wprowadzon� warto�� na wygenerowanym indeksie
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("TableMiddleAdding.txt");
		break;
	case '6':
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			table->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			table->insert_back(val);											//Umieszczamy warto�� na ko�cu tablicy
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("TableBackAdding.txt");
		break;
	case '7':
		for (unsigned int i = 0; i < 100; i++)
		{
			table->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			table->pop_front();													//Usuwamy warto�� z pocz�tku
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("TableFrontDeleting.txt");
		break;
	case '8':
		for (unsigned int i = 0; i < 100; i++)
		{
			table->populate(size);
			srand(time(NULL));
			int id = rand() % (size - 2) + 1;
			t1 = std::chrono::high_resolution_clock::now();
			table->remove(id);													//Usuwamy warto�� na losowo wygenerowanym indeksie
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("TableMiddleDeleting.txt");
		break;
	case '9':
		for (unsigned int i = 0; i < 100; i++)
		{
			table->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			table->pop_back();													//Usuwamy warto�� z ko�ca tablicy
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("TableBackDeleting.txt");
		break;
	case '0':
		table->display();														//Wy�wietlamy warto�ci tablicy
		getchar();
		break;
	case 'q':
		return;
	default:
		std::cout << "An unidentified option has been chosen, please input correct parameter to perfom an action!\n";
	}
	table->saveToFile("table.txt");
}

void MainMenu::listTimeExperiments(char option)
{
	int val;
	switch (option)
	{
	case '1':
		list->loadFromFile("lista.txt");
		break;
	case '2':
		this->restartList();												//Zerujemy list�, aby dodawa� elementy od zera
		list->populate(size);												//Zape�niamy list� losowymi liczbami
		std::cout << "The list has been populated with random numbers\n";
		getchar();
		break;
	case '3':
		std::cout << "Input a value you wish to find: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartList();
			ListElement *el;												//Tworzymy nowy wska�nik
			list->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			el = list->find(val);											//Ustawiamy stworzony wska�nik na wyszukan� warto��
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("ListSearch.txt");
		break;
	case '4':
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartList();
			list->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			list->push_front(val);											//Dodajemy element na pocz�tku listy
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("ListFrontAdding.txt");
		break;
	case '5':
		int succ;
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		std::cout << "Choose successor: ";
		succ = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartList();
			list->populate(size);
			ListElement *el = list->find(succ);								//Tworzymy nowy wska�nik i ustawiamy go na wyszukan� warto�� nast�pnika
			t1 = std::chrono::high_resolution_clock::now();
			list->push(val, el);											//Dodajemy nowy element o zadanej warto�ci przed wyszukanym elementem
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("ListMiddleAdding.txt");
		break;
	case '6':
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartList();
			list->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			list->push_back(val);											//Dodajemy element na ko�cu listy
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("ListBackAdding.txt");
		break;
	case '7':
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartList();
			list->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			list->pop_front();												//Usuwamy element z pocz�tku listy
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("ListFrontDeleting.txt");
		break;
	case '8':
		std::cout << "Input a value you wish to remove: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartList();
			ListElement *el;
			list->populate(size);
			el = list->find(val);
			t1 = std::chrono::high_resolution_clock::now();
			list->remove(el);												//Usuwamy element o zadanej warto�ci
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("ListMiddleDeleting.txt");
		break;
	case '9':
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartList();
			list->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			list->pop_back();												//Usuwamy element z ko�ca listy
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("ListBackDeleting.txt");
		break;
	case '0':
	{
		int lcount = list->getCount();
		if (lcount != 0) list->display();
		getchar();
		break;
	}
	case 'q':
		return;
	default:
		std::cout << "An unidentified option has been chosen, please input correct parameter to perfom an action!\n";
	}
	list->saveToFile("list.txt");
}

void MainMenu::heapTimeExperiments(char option)
{
	int val;
	switch (option)
	{
	case '1':
		heap->loadFromFile("kopiec.txt");
		break;
	case '2':
		this->restartHeap();
		heap->populate(size);
		std::cout << "The heap has been populated with random numbers\n";
		getchar();
		break;
	case '3':
		std::cout << "Input a value you wish to find: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartHeap();
			heap->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			heap->find(val);
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("HeapSearch.txt");
		break;
	case '4':
		std::cout << "Input a value you wish to add: ";
		val = checkInt(1, 20000);
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartHeap();
			heap->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			heap->push(val);
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		saveResultsToFile("HeapAdding.txt");
		break;
	case '5':
		for (unsigned int i = 0; i < 100; i++)
		{
			this->restartHeap();
			heap->populate(size);
			t1 = std::chrono::high_resolution_clock::now();
			heap->pop();
			t2 = std::chrono::high_resolution_clock::now();
			results[i] = saveCountTime();
		}
		calcAverage();
		std::cout << "The last leaf has been removed\n";
		saveResultsToFile("HeapPopping.txt");
		break;
	case '0':
		heap->display(std::cout);
		getchar();
		break;
	case 'q':
		return;
	default:
		std::cout << "An unidentified option has been chosen, please input correct parameter to perfom an action!\n";
	}
	heap->saveToFile("heap.txt");
}

//Metoda pobieraj�ca tekst menu pomiar�w czasu tablicy
std::string MainMenu::getTableTimeMenu()
{
	return this->tableTimeMenu;
}

//Metoda pobieraj�ca tekst menu pomiar�w czasu listy
std::string MainMenu::getListTimeMenu()
{
	return this->listTimeMenu;
}

//Metoda pobieraj�ca tekst menu pomiar�w czasu kopca
std::string MainMenu::getHeapTimeMenu()
{
	return this->heapTimeMenu;
}

//Metoda ustawiaj�ca tekst menu pomiar�w czasu tablicy
void MainMenu::setTableTimeMenu()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a nast�pnie pobieramy je do jednego stringa
	ss << "Array measurements:\n";
	ss << "[1] Load array from file\n" << "[2] Fill the array with random numbers\n" << "[3] Measure the time of searching\n";
	ss << "[4] Measure the time of adding in front\n" << "[5] Measure the time of adding in the middle\n";
	ss << "[6] Measure the time of adding at the end\n" << "[7] Measure the time of deleting in the front\n";
	ss << "[8] Measure the time of deleting in the middle\n" << "[9] Measure the time of deleting at the end\n";
	ss << "[0] Show contents of the table\n" << "[q] Return to main menu\n" << "\nYour choice: ";
	this->tableTimeMenu = ss.str();
}

//Metoda ustawiaj�ca tekst menu pomiar�w czasu listy
void MainMenu::setListTimeMenu()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a nast�pnie pobieramy je do jednego stringa
	ss << "Doubly linked list measurements:\n";
	ss << "[1] Load the list from file\n" << "[2] Fill the list with random numbers\n" << "[3] Measure the time of searching\n";
	ss << "[4] Measure the time of adding in front\n" << "[5] Measure the time of adding in the middle\n";
	ss << "[6] Measure the time of adding at the end\n" << "[7] Measure the time of deleting in the front\n";
	ss << "[8] Measure the time of deleting in the middle\n" << "[9] Measure the time of deleting at the end\n";
	ss << "[0] Show contents of the list\n" << "[q] Return to main menu\n" << "\nYour choice: ";
	this->listTimeMenu = ss.str();
}

//Metoda ustawiaj�ca tekst menu pomiar�w czasu kopca
void MainMenu::setHeapTimeMenu()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a nast�pnie pobieramy je do jednego stringa
	ss << "Binary heap measurements:\n";
	ss << "[1] Load the heap from file\n" << "[2] Fill the heap with random numbers\n" << "[3] Measure the time of searching\n";
	ss << "[4] Measure the time of adding to heap\n" << "[5] Measure the time of removing the root\n";
	ss << "[0] Show contents of the heap\n" << "[q] Return to main menu\n" << "\nYour choice: ";
	this->heapTimeMenu = ss.str();
}

int MainMenu::checkInt(int min, int max)
{
	int input;
	while (!(std::cin >> input) || (input < min) || (input > max) || std::cin.peek() != '\n')
	{
		std::cout << "You must input a whole number between " << min << " and " << max << "!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return input;
}