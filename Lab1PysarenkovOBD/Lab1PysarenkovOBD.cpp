#include <iostream>
#include "Structs.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "������ ��������\n";
	while (true) {
		std::cout << "\n������ 0, ��� ����� �� ��������\n";
		std::cout << "1 - ������ ���������\n";
		std::cout << "2 - ������ ���������\n";
		std::cout << "3 - ������ ��� ��� ���������\n";
		std::cout << "4 - �������� ���������\n";
		std::cout << "5 - ������ ����\n";
		std::cout << "6 - ������ ����\n";
		std::cout << "7 - ������ ��� ��� ����\n";
		std::cout << "8 - �������� ����\n";
		std::cout << "9 - ������� �� ��������\n";
		std::cout << "10 - ������� �� ���\n";
		std::cout << "11 - ������� �� ��� ���������\n";
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

