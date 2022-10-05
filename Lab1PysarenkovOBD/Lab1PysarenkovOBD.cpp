#include <iostream>
#include "Structs.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Музичні фестивалі\n";
	while (true) {
		std::cout << "\nВведіть 0, щоб вийти із програми\n";
		std::cout << "1 - Додати фестиваль\n";
		std::cout << "2 - Знайти фестиваль\n";
		std::cout << "3 - Змінити дані про фестиваль\n";
		std::cout << "4 - Видалити фестиваль\n";
		std::cout << "5 - Додати пісню\n";
		std::cout << "6 - Знайти пісню\n";
		std::cout << "7 - Змінити дані про пісню\n";
		std::cout << "8 - Видалити пісню\n";
		std::cout << "9 - Вивести всі фестивалі\n";
		std::cout << "10 - Вивести всі пісні\n";
		std::cout << "11 - Вивести всі пісні фестивалю\n";
		int op;
		std::cin >> op;
		switch (op) {
		case 0:
			return 0;
		case 1:
			insert_f();
			break;
		case 2:
			output_f(0);
			break;
		case 3:
			update_f();
			break;
		case 4:
			remove_f();
			break;
		case 5:
			insert_s();
			break;
		case 6:
			output_s(0);
			break;
		case 7:
			update_s();
			break;
		case 8:
			remove_s();
			break;
		case 9:
			output_f(-1);
			break;
		case 10:
			output_s(-2);
			break;
		case 11:
			output_s(-1);
			break;
		}
	}
}

