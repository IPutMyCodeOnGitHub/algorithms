#include<Windows.h>
#include<iostream>
#include"List.h"

typedef unsigned long long INT_64;

INT_64 lrand() {
	return rand() << 16 | rand();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List<int>* list = new List<int>();
	List<int>::Iterator iter(list);

	char com[128];
	std::cout << "------������������ ��� ''������''----------" << std::endl
		<< "help - ��������� � ���� " << std::endl;
	std::cin >> com;
	while (strcmp("stop", com) != 0) {
		if (strcmp("help", com) == 0)
		{
			std::cout << "" << std::endl
				<< "1. help -		������� ����" << std::endl
				<< "2. show -		������� ������" << std::endl
				<< "3. push -		��������� ������� � ������ ������" << std::endl
				<< "4. pushPos -	�������� ������� �� �������" << std::endl
				<< "5. delVal -		������� �� ��������" << std::endl
				<< "6. delPos -		������� �� �������" << std::endl
				<< "7. change -		�������� ������� �� �������" << std::endl
				<< "8. size -		����� ������� ������" << std::endl
				<< "9. empty -		�������� ������ �� �������" << std::endl
				<< "10. findVal -	����� ������� �� ��������" << std::endl
				<< "11. findPos -	����� ������� �� �������" << std::endl
				<< "12. isVal -		����� ������� ��������" << std::endl
				<< "13. clear -		�������� ������" << std::endl
				<< "14. test -		������������" << std::endl
				<< "  -------���� ���������" << std::endl
				<< "  first -	���������� �������� �� ������ ��������" << std::endl
				<< "  next -	������� � ���������� �������� ������" << std::endl
				<< "  state -	������ ��������� ���������" << std::endl
				<< "  write - ������ �� ������ � �������� ��������" << std::endl
				<< "  read - ������ �� ������ � �������� ��������" << std::endl;
		}
		if (strcmp("show", com) == 0)
		{
			list->showList();
			std::cout << std::endl;
		}
		if (strcmp("push", com) == 0)
		{
			int val;
			std::cout << "��������: " << std::endl;
			std::cin >> val;
			list->pushElem(val);
			std::cout << std::endl;
		}
		if (strcmp("pushPos", com) == 0)
		{
			int val, pos;
			std::cout << "�������� � �������: " << std::endl;
			std::cin >> val >> pos;
			std::cout << list->pushByPos(val, pos) << std::endl;
		}
		if (strcmp("delVal", com) == 0)
		{
			int val;
			std::cout << "��������: " << std::endl;
			std::cin >> val;
			std::cout << list->deleteByVal(val) << std::endl;
		}
		if (strcmp("delPos", com) == 0)
		{
			int pos;
			std::cout << "�������: " << std::endl;
			std::cin >> pos;
			std::cout << list->deleteByPos(pos) << std::endl;
		}
		if (strcmp("change", com) == 0)
		{
			int val, pos;
			std::cout << "������� � ����� ��������: " << std::endl;
			std::cin >> pos >> val;
			std::cout << list->changeElem(pos, val) << std::endl;
		}
		if (strcmp("size", com) == 0)
		{
			std::cout << "������ ������: " << list->getSize() << std::endl;
		}
		if (strcmp("empty", com) == 0)
		{
			std::cout << list->isEmpty() << std::endl;
		}
		if (strcmp("findVal", com) == 0)
		{
			int val;
			std::cout << "��������: " << std::endl;
			std::cin >> val;
			std::cout << list->findVal(val) << std::endl;
			std::cout << std::endl;
		}
		if (strcmp("findPos", com) == 0)
		{
			int pos;
			std::cout << "�������: " << std::endl;
			std::cin >> pos;
			try
			{
				std::cout << "��������: " << list->findPos(pos) << std::endl;
			}
			catch (ListError* er)
			{
				er->Error();
			}
			std::cout << std::endl;
		}
		if (strcmp("isVal", com) == 0)
		{
			int val;
			std::cout << "��������: " << std::endl;
			std::cin >> val;
			std::cout << list->isVal(val) << std::endl;
		}
		if (strcmp("clear", com) == 0)
		{
			list->clearList();
			std::cout << std::endl;
		}
		if (strcmp("first", com) == 0)
		{
			std::cout << iter.first() << std::endl;
		}
		if (strcmp("next", com) == 0)
		{
			std::cout << iter.next() << std::endl;
		}
		if (strcmp("state", com) == 0)
		{
			std::cout << iter.isOff();
		}
		if (strcmp("write", com) == 0)
		{
			try
			{
				
				std::cin >> *iter;
			}
			catch (ListError* er)
			{
				er->Error();
			}
		}
		if (strcmp("read", com) == 0)
		{
			try
			{
				std::cout << *iter;
			}
			catch (ListError* er)
			{
				er->Error();
			}
		}
		if (strcmp("test", com) == 0)
		{
			int size = 0, from = 0, to = 0, insertCounter = 0, deleteCounter = 0, searchCounter = 0;
			std::cout << "������ ������: " << std::endl;
			std::cin >> size;
			std::cout << "������ ���������: " << std::endl;
			std::cin >> from;
			std::cout << "����� ���������: " << std::endl;
			std::cin >> to;
			for (int i = 0; i < size; i++)
			{
				list->pushElem(from + lrand() % (to - from));
			}
			for (int i = 0; i < size / 2; i++)
			{
				list->pushByPos(rand() % size * 2, lrand() % size - 1);
				insertCounter += list->getOperNum();
				list->deleteByPos(lrand() % size - 1);
				deleteCounter += list->getOperNum();
				list->findVal(from + lrand() % (to - from));
				searchCounter += list->getOperNum();
			}
			std::cout << "������: " << list->getSize() << std::endl;
			std::cout << "�������: " << insertCounter / (size / 2) << std::endl;
			std::cout << "��������: " << deleteCounter / (size / 2) << std::endl;
			std::cout << "�����: " << searchCounter / (size / 2) << std::endl;
			std::cout << "������ ������: " << list->getSize() << std::endl;
		}
		std::cin >> com;
	}
	system("pause");
	return 0;
}