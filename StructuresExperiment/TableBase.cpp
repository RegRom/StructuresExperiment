#include "stdafx.h"
#include "TableBase.h"


TableBase::TableBase()
{
	this->size = 0;
	this->content = new int[0];								//tworzenie pustej tabeli by zapobiec pr�bie usuni�cia nullptr
}

TableBase::TableBase(int _size)
{
	this->size = _size;
	this->content = new int[size];
}

TableBase::~TableBase()
{
}

//Metoda zamieniaj�ca elementy miejscami
void TableBase::swap(int & a, int & b)
{
	int buf = a;
	a = b;
	b = buf;
}

//Metoda �aduj�ca tablic� z pliku
void TableBase::loadFromFile(std::string fileName)
{
	std::fstream file;										//zmienna plikowa
	std::string line;										//string do przechowywania linii odczytanej z pliku

	file.open(fileName, std::ios::in);
	if (file.good())
	{
		int i = 0;
		getline(file, line);								//odczytanie pierwszej linii z pliku, tj. wielko�ci struktury
		int nSize = std::stoi(line);						//konwertujemy string do inta
		int *arr = new int[nSize];

		while (getline(file, line) && i < nSize)
		{
			arr[i++] = std::stoi(line);						//odczytujemy warto�ci z pliku
		}
		this->content = arr;
		this->size = nSize;
		std::cout << "Table has been loaded succesfully";
	}
	else {
		std::cout << "Failed to open the file, it may be corrupted";
	}
	file.close();
}

//Metoda zape�niaj�ca tablic� losowymi liczbami
void TableBase::populate(int _size)
{
	int *arr = new int[_size];
	srand(time(NULL));
	for (int i = 0; i < _size; i++)
	{
		int num = rand() % _size + 1;
		arr[i] = num;
	}
	this->content = arr;
	this->size = _size;
}

//Metoda zapisuj�ca tablic� do pliku
void TableBase::saveToFile(std::string fileName)
{
	std::fstream file;										//zmienna plikowa
	file.open(fileName, std::ios::out);						//otwarcie pliku do zapisu

	if (file.good())
	{
		file << size << "\n";								//zapis rozmiaru struktury do pierwszej linii
		for (unsigned int i = 0; i < size; i++)
		{
			file << content[i] << "\n";
		}
	}
	file.close();
}