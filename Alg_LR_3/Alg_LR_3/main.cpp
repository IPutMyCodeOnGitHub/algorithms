#include<Windows.h>
#include"AVL.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	BalanceTree<int, int>* tree = new BalanceTree<int, int>;

	tree->push(30,30);
	tree->show();
	std::cout << std::endl << std::endl;
	tree->push(40, 40);
	tree->show();
	std::cout << std::endl << std::endl;
	tree->push(50, 50);
	tree->show();
	std::cout << std::endl << std::endl;
	tree->push(60, 60);
	tree->show();
	std::cout << std::endl << std::endl;
	tree->push(20, 20);
	tree->show();
	std::cout << std::endl << std::endl;
	tree->push(10, 10);
	tree->show();
	std::cout << std::endl << std::endl;
	tree->push(1, 1);
	tree->show();
	std::cout << std::endl << std::endl;











	//BalanceTree<int, int>::Iterator iter(tree);

	/*char com[128];
	std::cout << "------������������ ��� ''AVL-������''----------" << std::endl
		<< "help - ��������� � ���� " << std::endl;
	std::cin >> com;
	while (strcmp("stop", com) != 0) {
		if (strcmp("help", com) == 0)
		{
			std::cout << "" << std::endl
				<< "1. help -		������� ����" << std::endl
				<< "2. show -		������� ������" << std::endl
				<< "3. push -		��������� ������� � ������ �� �����" << std::endl
				<< "4. del -		������� ������� �� �����" << std::endl
				<< "5. size -		�������� ������ ������" << std::endl
				<< "6. empty -		�������� ������ �� �������" << std::endl
				<< "7. find -		����� ������� �� �����" << std::endl
				<< "8. clear -		�������� ������" << std::endl
				<< "9. round -		������ ������ �� ����� Lt - t - Rt" << std::endl
				<< "10. length -	���������� ����� �������� ���� ������" << std::endl
				<< "11. test -		������������" << std::endl
				<< "  -------���� ���������" << std::endl
				<< "  first -	���������� �������� �� ������ ��������" << std::endl
				<< "  prev -	������� � ����������� �������� ������" << std::endl
				<< "  next -	������� � ���������� �������� ������" << std::endl
				<< "  state -	������ ��������� ���������" << std::endl
				<< "  read -	������ �� ������ � �������� ��������" << std::endl
				<< "  write -	������ �� ������ � �������� ��������" << std::endl;
		}
		if (strcmp("show", com) == 0)
		{
			tree->show();
			std::cout << std::endl;
		}
		if (strcmp("push", com) == 0)
		{
			int data, key;
			std::cout << "������ � ����: " << std::endl;
			std::cin >> data >> key;
			std::cout << tree->push(data, key) << std::endl;
		}
		if (strcmp("del", com) == 0)
		{
			int key;
			std::cout << "����: " << std::endl;
			std::cin >> key;
			std::cout << tree->deleteByKey(key) << std::endl;
		}
		if (strcmp("size", com) == 0)
		{
			std::cout << "������ ������: " << tree->getSize() << std::endl;
		}
		if (strcmp("empty", com) == 0)
		{
			std::cout << tree->empty() << std::endl;
		}
		if (strcmp("find", com) == 0)
		{
			int key;
			std::cout << "����: " << std::endl;
			std::cin >> key;
			try
			{
				std::cout << tree->getData(key);
			}
			catch (TreeError* er)
			{
				er->Error();
			}
			std::cout << std::endl;
		}
		if (strcmp("clear", com) == 0)
		{
			tree->clear();
			std::cout << std::endl;
		}
		if (strcmp("round", com) == 0)
		{
			tree->round();
			std::cout << std::endl;
		}
		if (strcmp("length", com) == 0)
		{
			std::cout << tree->outLength() << std::endl;
		}
		if (strcmp("first", com) == 0)
		{
			std::cout << iter.first() << std::endl;
		}
		if (strcmp("last", com) == 0)
		{
			std::cout << iter.last() << std::endl;
		}
		if (strcmp("prev", com) == 0)
		{
			std::cout << iter.prev() << std::endl;
		}
		if (strcmp("next", com) == 0)
		{
			std::cout << iter.next() << std::endl;
		}
		if (strcmp("state", com) == 0)
		{
			std::cout << iter.isOff() << std::endl;
		}
		if (strcmp("write", com) == 0)
		{
			try {
				std::cin >> *iter;
			}
			catch (TreeError* er) {
				er->Error();
			}
		}
		if (strcmp("read", com) == 0)
		{
			try {
				std::cout << *iter << std::endl;
			}
			catch (TreeError* er) {
				er->Error();
			}
		}
	}*/

	system("pause");
	return 0;
}