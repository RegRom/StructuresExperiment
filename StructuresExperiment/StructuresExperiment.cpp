// StructuresExperiment.cpp: Okre�la punkt wej�cia dla aplikacji konsoli.
//

#include "stdafx.h"
#include "DoublyLinkedList.h"
#include "BinaryHeap.h"
#include "Table.h"
#include "MainMenu.h"

//######## FUNKCJA DO SPRAWDZANIA POPRAWNO�CI WPROWADZONYCH WARTO�CI ########
int checkInt(int min, int max)
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

void normalMenu(int _size, int max, int min)
{
	MainMenu *menu = new MainMenu(_size);						//Tworzymy obiekt do zarz�dzania strukturami
	while (true) {
		int Option = 0;											//Wyb�r struktury, na kt�rej chcemy experymentowa�
		char expOption = 0;										//Wyb�r konkretnej czynno�ci jak� chcemy wykona� na sktrukturze
		std::cout << menu->getGreetingMessage();
		Option = checkInt(0, 7);								//Sprawdzamy czy wprowadzony wyb�r mie�ci si� w zbiorze mo�liwych

		if (Option == 1)										//Trzy pierwsze opcje s�u�� manipulacji strukturami
		{
			std::cout << menu->getTableMenu();
			std::cin >> expOption;
			menu->tableExperiments(expOption);

		}
		else if (Option == 2)
		{
			std::cout << menu->getListMenu();
			std::cin >> expOption;
			menu->listExperiments(expOption);
		}
		else if (Option == 3)
		{
			std::cout << menu->getHeapMenu();
			std::cin >> expOption;
			menu->heapExperiments(expOption);
		}
		if (Option == 4)										//Opcje 4-6 s�u�� do wykonywania pomiaru czasu operacji na strukturach
		{
			std::cout << menu->getTableTimeMenu();
			std::cin >> expOption;
			menu->tableTimeExperiments(expOption);

		}
		else if (Option == 5)
		{
			std::cout << menu->getListTimeMenu();
			std::cin >> expOption;
			menu->listTimeExperiments(expOption);
		}
		else if (Option == 6)
		{
			std::cout << menu->getHeapTimeMenu();
			std::cin >> expOption;
			menu->heapTimeExperiments(expOption);
		}
		else if (Option == 7)									//Opcja 7 pozwala zmieni� domy�lny rozmiar struktur
		{
			delete menu;
			std::cout << "Define the new size of the structures: ";
			_size = checkInt(min, max);							//Sprawdzamy czy rozmiar jest typu int

			MainMenu *menu = new MainMenu(_size);
		}
		else if (Option == 0)									//Wyj�cie z programu
		{
			delete menu;
			exit(0);
		}
		getchar();
		system("cls");
	}
}


int main()
{
	static const int MIN = 1;											//Minimalny rozmiar struktury
	static const int MAX = 20000;										//Maksymalny rozmiar struktury
	int structSize, input;
	std::cout << "Welcome to Data Structures Testing Program\n";
	std::cout << "Define the size of structures you want to test: ";
	structSize = checkInt(MIN, MAX);							//Sprawdzamy czy rozmiar jest prawid�owym intem

	system("cls");

	normalMenu(structSize, MIN, MAX);

	return 0;
}