#include "stdafx.h"
#include "DoublyLinkedList.h"


DoublyLinkedList::DoublyLinkedList()
{
	count = 0;
	head = new ListElement();
	tail = head;
}


DoublyLinkedList::~DoublyLinkedList()
{
	while (count > 0)
	{
		this->pop_back();						//usuwamy wszystkie elementy listy, poczynaj�c od ko�ca
	}
	delete head;
}

//Metoda dodaj�ca element z przodu listy
void DoublyLinkedList::push_front(int val)
{
	ListElement *el = new ListElement;					//Tworzymy nowy wska�nik na obiekt
	el->setData(val);									//Nadajemy mu warto�� z parametru
	count++;											//Zwi�kszamy licznik listy o jeden
	switch (count)
	{
	case 1:
		tail = el;										//Je�eli licznik wynosi 1 to ustawiamy nowy element jako ogon
		break;
	case 2:
		tail->setPrev(el);								//Je�li licznik wynosi 2 to ogon jest ustawiony, ale nie ma poprzednika, ustawiamy go
	default:
		el->setNext(head);								//Ustawiamy g�ow� jako nast�pnik elementu, kt�ry chcemy doda�
	}
	head = el;											//Nowy element staje si� g�ow�
	if (el->getNext() != nullptr || count == 2)
	{
		(el->getNext())->setPrev(el);					//Je�li nast�pnik dodawanego elementu nie jest nullptr to ustawiamy dodawany element
	}													//jako poprzednik ju� istniej�cego nast�pnika
}

//Metoda dodaj�ca element z ty�u listy
void DoublyLinkedList::push_back(int val)
{
	if (count == 0) push_front(val);
	else
	{
		ListElement *el = new ListElement();					//Tworzymy nowy wska�nik na obiekt
		el->setData(val);									//Nadajemy mu warto�� z parametru
		el->nullifyNext();									//Zerujemy nast�pnik
		el->setPrev(tail);									//Ustawiamy ogon jako poprzednika
		tail = el;											//Nowy element staje si� nowym ogonem
		count++;											//Zwi�kszamy licznik listy
		if (el->getPrev() != nullptr)
		{
			(el->getPrev())->setNext(el);					//Je�li poprzednik nie jest nullptr to ustawiamy dodawany element jako nast�pnika
		}													//istniej�cego ju� poprzednika
		else this->head = el;								//Je�li jest nullptr to znaczy, �e jest pierwszym elementem i staje si� g�ow�
	}
}

//Metoda dodajaca element w wybranym miejscu
void DoublyLinkedList::push(int val, ListElement *&p)	//Podajemy nast�pnika jako parametr
{
	if (p == head) push_front(val);
	else {
		ListElement *el = new ListElement;
		el->setData(val);
		el->setNext(p);									//Ustawiamy wska�nik z parametru jako nast�pnika
		el->setPrev(p->getPrev());						//Poprzednik nast�pnika staje si� poprzednikiem dodawanego elementu
		(p->getPrev())->setNext(el);					//Dodawany element staje si� nast�pnikiem poprzednika wska�nika podanego jako parametr
		p->setPrev(el);									//Nowy element staje si� poprzednikiem swojego nast�pnika
		count++;
	}
}

//Metoda usuwaj�ca element z przodu listy
void DoublyLinkedList::pop_front()
{
	if (count) remove(head);
}

//Metoda usuwaj�ca element z ty�u listy 
void DoublyLinkedList::pop_back()
{
	if (count) remove(tail);
}

//Metoda usuwaj�ca element w dowolnym miejscu
void DoublyLinkedList::remove(ListElement * p)
{
	if (p->getPrev()) (p->getPrev())->setNext(p->getNext());	//Je�li p ma poprzednika to nast�pnik p staje si� nastepnikiem jego poprzednika
	else head = p->getNext();									//W innym wypadku nast�pnik p staje si� g�ow�
	if (p->getNext()) (p->getNext())->setPrev(p->getPrev());	//Je�li p ma nast�pnika to poprzednik p staje si� poprzednikiem jego nast�pnika
	else tail = p->getPrev();									//W innym wypadku poprzednik p staje si� ogonem
	delete p;													//Usuwamy p i przypisujemy mu null
	p = nullptr;
	count--;													//Zmniejszamy licznik
}

//Metoda wyszukuj�ca warto�� w liscie
ListElement * DoublyLinkedList::find(int val)
{
	ListElement *p = new ListElement;							//Tworzymy wska�nik p i ustawiamy go na g�ow�
	p = head;
	while (p->getNext()) {										//Tak d�ugo jak p ma nast�pnik�w to iterujemy i sprawdzamy czy warto��
		if (val == p->getData())
		{
			std::cout << "Value has been found\n";
			return p;						//elementu zgadza si� z warto�ci� podan� jako parametr
		}
		else p = p->getNext();									//Je�li jest r�wna to zwracamy ten wska�nik, je�li nie to idziemy dalej
	}
	std::cout << "There is no such value in the list";
	return nullptr;
}

//Metoda wy�wietlaj�ca elementy listy
void DoublyLinkedList::display()
{
	ListElement *p = new ListElement;
	p = head;
	std::cout << "head->";
	for (int i = 0; i < count; i++)
	{
		std::cout << p->getData() << "->";
		p = p->getNext();
	}
	std::cout << "tail\n";
}

//Metoda wczytuj�ca elementy z pliku
void DoublyLinkedList::loadFromFile(std::string fileName)
{
	std::fstream file;
	std::string line;

	file.open(fileName, std::ios::in);
	if (file.good())
	{
		getline(file, line);
		int tmp_count = std::stoi(line);

		while (getline(file, line))										//Tak d�ugo jak w pliku s� warto�ci dodajemy je na pocz�tek listy
		{
			int val = std::stoi(line);
			push_front(val);
		}
	}
	else {
		std::cout << "Failed to open the file, it may be corrupted";
	}
	file.close();
}

//Metoda zape�niaj�ca list� losowymi elementami
void DoublyLinkedList::populate(int _size, int val)
{
	for (int i = 0; i < _size; i++)
	{														//Dodajemy elementy z przodu listy tak d�ugo, a� osi�gniemy zadany rozmiar	
		int num = rand() % _size + 1;						//Dodatkowo w losowo okre�lonym miejscu dodajemy jedn� sprecyzowan� warto��
		push_front(num);									//kt�ra jest podana jako parametr
	}
	this->count = _size;
}

//Metoda zapisuj�ca list� do pliku
void DoublyLinkedList::saveToFile(std::string fileName)
{
	std::fstream file;
	file.open(fileName, std::ios::out);

	if (file.good())
	{
		ListElement *p = head;
		file << count << "\n";
		for (unsigned int i = 0; i < count - 1; i++)
		{
			file << p->getData() << "\n";
			p = p->getNext();
		}
		file << p->getData() << "\n";
	}
	file.close();
}

void DoublyLinkedList::restartList()
{
	while (count > 0)
	{
		this->pop_back();
	}
}

int DoublyLinkedList::getCount()
{
	return count;
}