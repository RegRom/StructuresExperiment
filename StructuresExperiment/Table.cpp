#include "stdafx.h"
#include "Table.h"


Table::Table()
{
}

Table::Table(int _size)
	:TableBase(_size)								//wywo�anie konstruktora klasy bazowej
{
}


Table::~Table()
{
	delete[] content;
}

//Metoda dodaj�ca element z przodu tablicy
void Table::insert_front(int val)
{
	int newSize = size+1;							//Tworzymy now� tablic� o 1 element wi�ksz� od aktualnej,
	int *newArray = new int[newSize];				//dodajemy element na pierwszym miejscu
	newArray[0] = val;								//a nast�pnie przepisujemy do niej warto�ci z aktualnej tablicy
	for (int i = 1; i < newSize; i++)
	{
		newArray[i] = content[i-1];
	}
	delete[] content;
	content = newArray;								//zast�pujemy star� tablic� now� tablic� 
	size = newSize;
}

//Metoda dodaj�ce element na ko�cu tablicy
void Table::insert_back(int val)
{
	int newSize = size+1;
	int *newArray = new int[newSize];				//Analogicznie jak przy dodawaniu na pocz�tku tablicy, lecz tym razem
	for (int i = 0; i < newSize-1; i++)				//najpierw przepisujemy warto�ci, a potem dodajemy now� warto�� na ko�cu
	{
		newArray[i] = content[i];
	}
	newArray[newSize-1] = val;
	delete[] content;
	content = newArray;
	size = newSize;
}

//Metoda dodaj�ce element w dowolnym miejscu
void Table::insert(int val, int id)
{
	int newSize = size+1;
	int *newArray = new int[newSize];				
	for (int i = 0; i < id; i++)					//Przepisujemy warto�ci z starej tablicy a� do indeksu gdzie chcemy wstawi� now� warto��
	{												
		newArray[i] = content[i];
	}
	newArray[id] = val;								//Wstawiamy now� warto�� na wybranym indeksie
	for (int j = id+1; j < newSize; j++)
	{
		newArray[j] = content[j-1];					//Przepisujemy reszt� warto�ci
	}
	delete[] content;
	content = newArray;
	size = newSize;
}

//Metoda usuwaj�ca element z przodu
void Table::pop_front()
{
	if (size > 0) 
	{
		int newSize = size - 1;							//Tworzymy now� tablic� o jeden element mniejsz�
		int *newArray = new int[newSize];
		for (int i = 0; i < newSize; i++)				//Przepisujemy do niej wszystkie warto�ci opr�cz pierwszej
		{
			newArray[i] = content[i + 1];
		}
		delete[] content;
		content = newArray;
		size = newSize;									//Nadpisujemy tablic�
	}
	else std::cout << "Array is empty\n";
	getchar();
}

//Metoda usuwaj�ca element z ty�u
void Table::pop_back()
{
	if(size > 0)
	{
		int newSize = size-1;							//Analogicznie jak przy usuwaniu z przodu, ale nie przepisujemy ostatniej warto�ci
		int *newArray = new int[newSize];
		for (int i = 0; i < newSize; i++)
		{
			newArray[i] = content[i];
		}
		delete[] content;
		content = newArray;
		size = newSize;
	}
	else std::cout << "Array is empty\n";
	getchar();
}


//Metoda usuwaj�ca element w dowolnym miejscu
void Table::remove(int id)
{
	if(size > 0)
	{ 
		int newSize = size-1;
		int *newArray = new int[newSize];				//Tworzymy now� tablic� i przepisujemy do niej wszystkie elementy opr�cz
		for (int i = 0; i < id; i++)					//elementu na jednej okre�lonej jako parametr pozycji
		{
			newArray[i] = content[i];
		}
		for (int i = id; i < newSize; i++)
		{
			newArray[i] = content[i+1];
		}
		delete[] content;
		content = newArray;
		size = newSize;
	}
	else std::cout << "Array is empty";
	getchar();
}

//Metoda wy�wietlaj�ca zawarto�� tablicy
void Table::display()
{
	for (unsigned int i = 0; i < (this->size); i++)			
	{
		std::cout << "|" << this->content[i];				//Iterujemy po tablicy i wy�wietlamy po kolei jej elementy oddzielaj�c znakiem
	}														// "|" jak w kom�rkach tabeli
	std::cout << "|";
}

//Metoda wyszukuj�ca warto�� w tablicy
void Table::find(int val)
{
	int counts = 0;
	for (unsigned int i = 0; i<(this->size); i++)								//Iterujemy po tablicy i sprawdzamy czy warto�� jest r�wna
	{																			//parametrowi metody
		if (val == content[i])													
		{
			std::cout << "Specified value is on at index i = " << i << "\n";
			counts++;															//Je�li tak to zwi�kszamy licznik wyst�pie�
		}
	}
	if (counts == 0) std::cout << "There is no such value in this array\n";
	else std::cout << "Value has been found " << counts << " times\n";
}