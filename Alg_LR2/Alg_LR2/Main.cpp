//вариант 2
//• Алгоритмы операций АТД реализуются в итеративной фор-ме.
//• Схема операции обхода : Lt → t → Rt.
//• Дополнительная операция : определение длины внешнего пути дерева(рекурсивная форма алгоритма).
#include<stack>
#include<Windows.h>
//#include<cstdlib>
#include"BST.h"

typedef unsigned long long INT_64;

INT_64 lrand() {
	return rand() << 16 | rand();
}

void test_rand(int n) {
	Tree<int, INT_64> tree;

	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++)
	{
		m[i] = lrand();
		tree.push(1, m[i]);
	}


	double I = 0;
	double D = 0;
	double S = 0;

	for (int i = 0; i < n / 2; i++)
		if (i % 10 == 0) {
			{
				tree.deleteByKey(lrand());
				D += tree.getOperNum();
				tree.push(1, m[rand() % n]);
				I += tree.getOperNum();
				try {
					tree.getData(lrand());
					S += tree.getOperNum();
				}
				catch (TreeError* e) { S += tree.getOperNum(); }
			}
		}
		else {
			int ind = rand() % n;
			tree.deleteByKey(m[ind]);
			D += tree.getOperNum();
			INT_64 key = lrand();
			tree.push(1, key);
			I += tree.getOperNum();
			m[ind] = key;
			try {
				tree.getData(m[rand() % n]);
				S += tree.getOperNum();
			}
			catch (TreeError* e) { S += tree.getOperNum(); }

		}


	std::cout << "items count:" << tree.getSize() << std::endl;
	std::cout << "1.39*log2(n)=" << 1.39*(log(n) / log(2)) << std::endl;
	std::cout << "Count insert: " << I / (n / 2) << std::endl;
	std::cout << "Count delete: " << D / (n / 2) << std::endl;
	std::cout << "Count search: " << S / (n / 2) << std::endl;
	delete[] m;
}


void test_sort(int n) {
	Tree<int, INT_64> tree;
	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++) {
		m[i] = i * 1000;
		tree.push(1, m[i]);
	}

	std::cout << "items count:" << tree.getSize() << std::endl;
	double I = 0;
	double D = 0;
	double S = 0;

	for (int i = 0; i < n / 2; i++) {
		if (i % 10 == 0)
		{
			int k = lrand() % (1000 * n);
			k = k + !(k % 2);
			tree.deleteByKey(k);
			D += tree.getOperNum();
			tree.push(1, m[rand() % n]);
			I += tree.getOperNum();
			k = lrand() % (1000 * n);
			k = k + !(k % 2);
			try {
				tree.getData(k);
				S += tree.getOperNum();
			}
			catch (TreeError* e) { S += tree.getOperNum(); }
		}
		else
		{
			int ind = rand() % n;
			tree.deleteByKey(m[ind]);
			D += tree.getOperNum();
			int k = lrand() % (1000 * n);
			k = k + k % 2;
			tree.push(1, k);
			I += tree.getOperNum();
			m[ind] = k;
			try {
				tree.getData(m[rand() % n]);
				S += tree.getOperNum();
			}
			catch (TreeError* e) { S += tree.getOperNum(); }

		}
	}
		std::cout << "items count:" << tree.getSize() << std::endl;
		std::cout << "n/2=" << n / 2 << std::endl;
		std::cout << "Count insert: " << I / (n / 2) << std::endl;
		std::cout << "Count delete: " << D / (n / 2) << std::endl;
		std::cout << "Count search: " << S / (n / 2) << std::endl;
		delete[] m;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Tree<int,int>* tree = new Tree<int,int>;
	
	Tree<int, int>::Iterator iter(tree);

	char com[128];
	std::cout << "------Тестирование АТД ''BST-дерево''----------" << std::endl
		<< "help - сообщение с меню " << std::endl;
	std::cin >> com;
	while (strcmp("stop", com) != 0) {
		if (strcmp("help", com) == 0)
		{
			std::cout << "" << std::endl
				<< "1. help -		вывести меню" << std::endl
				<< "2. show -		вывести дерево" << std::endl
				<< "3. push -		поместить элемент в дерево по ключу" << std::endl
				<< "4. del -		удалить элемент по ключу" << std::endl
				<< "5. size -		опросить размер дерева" << std::endl
				<< "6. empty -		проверка дерева на пустоту" << std::endl
				<< "7. find -		найти элемент по ключу" << std::endl
				<< "8. clear -		очистить дерево" << std::endl
				<< "9. round -		обойти дерево по схеме Lt - t - Rt" << std::endl
				<< "10. length -	определить длину внешнего пути дерева" << std::endl
				<< "11. test -		тестирование" << std::endl
				<< "  -------Меню итератора" << std::endl
				<< "  first -	установить итератор на первое значение" << std::endl
				<< "  prev -	перейти к предыдущему элементу дерева" << std::endl
				<< "  next -	перейти к следующему элементу дерева" << std::endl
				<< "  state -	узнать состояние итератора" << std::endl
				<< "  read -	доступ по чтению к текущему значению" << std::endl
				<< "  write -	доступ по записи к текущему значению" << std::endl;
		}
		if (strcmp("show", com) == 0)
		{
			tree->show();
			std::cout << std::endl;
		}
		if (strcmp("push", com) == 0)
		{
			int data, key;
			std::cout << "Данные и ключ: " << std::endl;
			std::cin >> data >> key;
			std::cout << tree->push(data, key) << std::endl;
		}
		if (strcmp("del", com) == 0)
		{
			int key;
			std::cout << "Ключ: " << std::endl;
			std::cin >> key;
			std::cout << tree->deleteByKey(key) << std::endl;
		}
		if (strcmp("size", com) == 0)
		{
			std::cout << "Размер дерева: " << tree->getSize() << std::endl;
		}
		if (strcmp("empty", com) == 0)
		{
			std::cout<< tree->empty() << std::endl;
		}
		if (strcmp("find", com) == 0)
		{
			int key;
			std::cout << "Ключ: " << std::endl;
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
			try{
				std::cin >> *iter;
			}
			catch (TreeError* er){
				er->Error();
			}
		}
		if (strcmp("read", com) == 0)
		{
			try{
				std::cout << *iter << std::endl;
			}
			catch (TreeError* er){
				er->Error();
			}
		}
		if (strcmp("new", com) == 0)
		{
			int balance;
			std::cin >> balance;
		}
		if (strcmp("test", com) == 0)
		{
			int size;
			std::cout << "Tree size: " << std::endl;
			std::cin >> size;
			test_rand(size);
			std::cout << std::endl;
			test_sort(size);
			std::cout << std::endl;

			/*int size = 0, from = 0, to = 0, insertCounter = 0, deleteCounter = 0, searchCounter = 0;
			std::cout << "Размер списка: " << std::endl;
			std::cin >> size;
			std::cout << "Начало интервала: " << std::endl;
			std::cin >> from;
			std::cout << "Конец интервала: " << std::endl;
			std::cin >> to;
			for (int i = 0; i < size; i++)
			{
				list->pushElem(from + rand() % (to - from));
			}
			for (int i = 0; i < size / 2; i++)
			{
				list->pushByPos(rand() % size * 2, rand() % size - 1);
				insertCounter += list->getOperNum();
				list->deleteByPos(rand() % size - 1);
				deleteCounter += list->getOperNum();
				list->findVal(from + rand() % (to - from));
				searchCounter += list->getOperNum();
			}
			std::cout << "Размер: " << list->getSize() << std::endl;
			std::cout << "Вставка: " << insertCounter / (size / 2) << std::endl;
			std::cout << "Удаление: " << deleteCounter / (size / 2) << std::endl;
			std::cout << "Поиск: " << searchCounter / (size / 2) << std::endl;
			std::cout << "Размер списка: " << list->getSize() << std::endl;*/

		}
		std::cin >> com;
	}

	system("pause");
	return 0;
}