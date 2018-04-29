#include "stdafx.h"
#include "BinaryHeap.h"


BinaryHeap::BinaryHeap()
{
}


BinaryHeap::~BinaryHeap()
{
	delete[] content;
}

//Metoda wy�wietlaj�ca kopiec 
void BinaryHeap::display(std::ostream & out)	//Podajemy strumie� wyj�ciowy i wypisujemy do niego obiekt
{
	if (size < 1)
	{
		std::cout << "Heap is empty\n";
		return;
	}
	draw(out, 0);								//Wywo�ujemy metod� rysuj�c� kopiec 
}

//Metoda usuwaj�ca korze�
void BinaryHeap::pop()
{
	if (size > 1)
	{
		int nSize = size - 1;
		int i, j = 1;
		int tmp = content[nSize];					//zapisujemy ostatni li�� do zmiennej
		int *newArray = new int[nSize];
		newArray[0] = tmp;							//Ustawiamy go jako korze� kopca

		for (i = 1; i < nSize; i++)
		{
			newArray[i] = content[i];				//Przepisujemy warto�ci
		}
		if (content) delete[] content;				//Usuwamy star� tablic� przechowuj�c� kopiec
		this->content = newArray;					//Nadpisujemy star� tablic�
		this->size = nSize;
		moveDown(0);								//Wywo�ujemy metod� naprawy kopca
	}
	else if (size == 1)
	{
		delete[] content;
		content = new int[0];
		size = 0;
		return;
	}
	else
	{
		std::cout << "The heap is empty\n";
		getchar();
	}
}

//Metoda dodaj�ca element jako ostatni li�� 
void BinaryHeap::push(int val)
{
	unsigned int nSize = size + 1;
	int *newArray = new int[nSize];					//Tworzymy now� tablic� o 1 wi�ksz�
	if (size == 0) newArray[size] = val;			//Je�li stara tablica by�a pusta to jedynie ustawiamy pierwszy element
	else {
		for (unsigned int i = 0; i < size; i++)
		{
			newArray[i] = content[i];				//W innym wypadku przepisujemy warto�ci, a now� warto�� wpisujemy na ostatni indeks
		}											//czyli jako ostatni li��
		newArray[size] = val;
	}
	delete[] content;
	this->content = newArray;
	moveUp(size);									//Naprawiamy kopiec
	this->size += 1;
}

//Metoda wyszukuj�ca element w kopcu
void BinaryHeap::find(int val)
{
	int tmpSize = size;
	int *tmpArray = new int[tmpSize];
	for (unsigned int i = 0; i < size - 1; i++)						//Tworzymy tymczasow� tablic� i przepisujemy do niej warto�ci z kopca
	{
		tmpArray[i] = content[i];
	}
	bool found = false;
	do
	{
		if (size > 1)
		{
			if (content[0] != val) {								//Tak d�ugo jak kopiec nie jest pusty i korze� nie jest r�wny szukanej
				pop();												//warto�ci, usuwamy korze�
			}
			else {
				std::cout << "Sought value has been found\n";
				found = true;
			}
		}
		else {
			if (content[0] == val) {
				std::cout << "Sought value has been found\n";
				found = true;
			}
			else {
				std::cout << "There is no such value in the heap\n";
				found = true;
			}
		}
	} while (!found);
	delete[] content;
	this->content = tmpArray;										//Przywracamy usuni�te warto�ci z kopca
	this->size = tmpSize;
}

//Metoda naprawiaj�ca kopiec w d�
void BinaryHeap::moveDown(int begin) {
	unsigned int lgSon = 2 * begin + 1;			//syn w�z�a, od kt�rego zaczynamy sortowa�
	while (lgSon <= size - 1) {

		if (lgSon < size - 1 && content[lgSon] < content[lgSon + 1]) lgSon++; //sprawdzamy czy drugi syn jest wi�kszy, je�li tak to wybieramy jego
		if (content[begin] < content[lgSon]) {

			swap(content[begin], content[lgSon]);							//Zamieniamy w�z�y miejscami
			begin = lgSon;													//przechodzimy w d� drzewa
			lgSon = 2 * begin + 1;
		}
		else {
			lgSon = size;
		}
	}
}

//Metoda wczytuj�ca kopiec z pliku
void BinaryHeap::loadFromFile(std::string fileName)
{
	std::fstream file;
	std::string line;

	file.open(fileName, std::ios::in);
	if (file.good())
	{
		int i = 0;
		getline(file, line);
		int nSize = std::stoi(line);
		int *arr = new int[nSize];

		while (getline(file, line) && i < nSize)
		{
			push(std::stoi(line));
		}
		this->size = nSize;
		std::cout << "Heap has been loaded succesfully";
	}
	else {
		std::cout << "Failed to open the file, it may be corrupted";
	}
	file.close();
}

//Metoda naprawiaj�ca kopiec w g�r� 
void BinaryHeap::moveUp(int sID)				//przekazujemy parametr syna, od kt�rego zaczynamy napraw�
{
	int tmp;
	if (sID != 0) {
		unsigned int pID = (sID - 1) / 2;		//Wyliczamy indeks rodzica
		if (content[pID] < content[sID]) {		//Je�li rodzic jest mniejszy od dziecka

			tmp = content[pID];					//zapisujemy warto�� rodzica do bufora
			content[pID] = content[sID];		//Zamieniamy miejscami rodzica z dzieckiem 
			content[sID] = tmp;
			moveUp(pID);						//Wywo�ujemy rekurencyjnie dla rodzica i idziemy w g�r� 
		}
	}
}

//Metoda zape�niaj�ca kopiec losowymi liczbami
void BinaryHeap::populate(int _size)
{
	srand(time(NULL));
	for (int i = 0; i < _size; i++)
	{
		int num = rand() % _size + 1;
		this->push(num);
	}
	size = _size;
}

//Metoda rysuj�ca kopiec 
void BinaryHeap::draw(std::ostream & output, int id)
{
	unsigned int child = 2 * id + 2;				//indeks syna kt�rego zaczynamy rysowanie

	if (child < size)								//je�li taki syn istnieje to rekurencyjnie wywo�ujemy metod� dla niego
		draw(output, child);

	int elem_lvl = (int)log2(id);					//Obliczamy poziom, na kt�rym znajduje si� element

	if (id == (int)exp2(elem_lvl + 1) - 1)
		elem_lvl++;									//Je�eli to maksymalnie lewy syn to obliczenie da nam poziom o jeden ni�szy, dodajemy wtedy

	for (int i = 0; i < elem_lvl * 3; i++)			//Wypisujemy odpowiedni� ilo�� spacji, nast�pnie jedno miejsce przed warto�ci� w�z�a
	{												/*   wypisujemy / lub \           */
		if (i == elem_lvl * 3 - 1)
		{
			if (id % 2 == 0)
				output << "/";
			else
				output << "\\";
		}
		else
			output << " ";
	}
	output << content[id] << "\n";					//Wypisujemy warto�� w�z�a
	child = 2 * id + 1;								//Obliczamy indeks lewego syna
	if (child < size)								//Je�li syn istnieje do wywo�ujemy rekurencyjnie metod� dla niego 
		draw(output, child);
}
