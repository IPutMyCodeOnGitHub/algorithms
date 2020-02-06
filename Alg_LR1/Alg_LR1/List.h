//#pragma once
//кольцевая, односвязная на базе адресных указателей
#include "Except.h"
template <class T>
class List
{
protected:
	class Node //вложенный класс элемента
	{
	public:
		T item; //значение узла
		Node* next; //указатель на следующий узел в списке
		Node(); //конструктор узла без параметров
		Node(T); //конструктор узла с параметром
		Node(const Node&); //конструктор копирования узла
		~Node(); //деструктор узла
	};

	Node* head; //указатель на первый узел
	int size; //количество элементов в списке
	int operNum; //количество операций

public:
	List(); //конструктор списка по умолчанию
	List(const List<T>&); //конструктор копирования
	~List(); //деструктор списка
	int getOperNum(); // опрос числа элементов списка, просмотренных операцией
	void showList(); //печать списка
	void pushElem(T); //поместить элемент в начало списка
	bool pushByPos(T, int); //поместить элемент по заданной позиции
	bool deleteByVal(T); //удалить по заданному значению
	bool deleteByPos(int); //удалить по заданной позиции
	int findVal(T); //получение позиции элемента с заданным значением
	int getSize(); //получить текущий размер списка
	void clearList(); //очистить список
	bool isEmpty(); //проверка списка на пустоту
	
	bool changeElem(int, T); //изменение значения элемента по заданной позиции
	T findPos(int); //получение значения по заданной позиции
	bool isVal(T); //опрос наличия заданного элемента


	class Iterator //вложенный класс, выполняющий функции итератора
	{
	public:
		List* ptr; //текущий список
		Node* cur; //текущий элемент списка
		Iterator(); //конструктор итератора по умолчанию
		Iterator(List* lst); //конструктор итератора с параметром
		~Iterator(); //деструтор итератора
		bool first(); //переход на начало списка
		bool next(); //переход к следующему элементу
		bool end(); //переход на конец списка
		bool isOff(); //проверка состояния итератора (внутри списка/вне списка)
		T& operator*(); //оператор доступа по чтению/записи
	};
};

template<class T>
inline List<T>::List()
{
	size = 0;
	head = nullptr;
}


template<class T>
inline List<T>::List(const List<T>& anotherList)
{
	Iterator iterNew;
	Iterator iterSource = new Iterator(anotherList);
	for (size = 0; size < anotherList->size; size++, iterSource.next(), iterNew.next())
	{
		if (head == nullptr)
		{
			head = new Node(iterSource->cur);
			iterNew = new Iterator(this);
			continue;
		}
		iterNew->cur.item = iterSource->cur.item;
		iterNew->cur.next = new Node(iterSource->cur);
		iterNew->cur.next = iterSource->cur.next;
	}
}

template<class T>
inline List<T>::~List()
{
	Iterator* iter = new Iterator(this);
	do
	{
		Node* tmp = new Node();
		tmp = iter->cur;
		iter->next();
		delete tmp;
	} while (--size > 0);
	head = nullptr;
}

template<class T>
inline int List<T>::getOperNum()
{
	return operNum;
}

template<class T>
inline void List<T>::showList()
{
	if (size == 0)
	{
		std::cout << "The List is empty!" << std::endl;
		return;
	}
	Iterator* iter = new Iterator(this);
	int k = 0;
	while (k < size) 
	{
		std::cout << iter->cur->item << std::endl;
		iter->next();
		k++;
	}
}

template<class T>
inline void List<T>::pushElem(T obj)
{
	if (head == nullptr)
	{
		head = new Node(obj);
		head->next = head;
		size++;
		return;
	}
	
	Node* newHead = new Node(obj);
	newHead->next = head;
	head = newHead;
	size++;
	Iterator* iter = new Iterator(this);
	iter->end();
	iter->cur->next = head;
	return;
}

template<class T>
inline bool List<T>::pushByPos(T object, int position)
{
	operNum = 0;
	if (position == 0) {
		pushElem(object);
		operNum++;
		return true;
	}
	if (position > size)
		return false;
	Iterator* iter = new Iterator(this);
	for (int i = 0; i < position - 1; i++, iter->next(), operNum++);
	Node* tmp = new Node(object);
	tmp->next = new Node(*(iter->cur->next));
	iter->cur->next = tmp;
	size++;
	return true;
}

template<class T>
inline bool List<T>::deleteByVal(T object)
{
	Iterator* iter = new Iterator(this);
	for (int i = 0; i < size; i++, iter->next())
	{
		if (iter->cur->next->item == object)
		{
			if (iter->cur->next == head)
			{
				head = head->next;
				iter->cur->next = head;
				size--;
				return true;
			}
			iter->cur->next = iter->cur->next->next;
			size--;
			return true;
		}
	}
	return false;
}

template<class T>
inline bool List<T>::deleteByPos(int position)
{
	operNum = 0;
	if (position >= size)
		return false;
	Iterator* iter = new Iterator(this);
	if (position == 0)
	{
		head = head->next;
		iter->end();
		iter->cur->next = head;
		size--;
		operNum++;
		return true;
	}
	for (int i = 0; i < position - 1; i++, iter->next(), operNum++);
	iter->cur->next = iter->cur->next->next;
	size--;
	return true;
}

template<class T>
inline int List<T>::findVal(T object)
{
	operNum = 0;
	Iterator* iter = new Iterator(this);
	int position = 0;
	do
	{
		if (iter->cur->item == object)
			return position;
		position++;
		iter->next();
		operNum++;
	} while (position < size);
	return -1;
}

template<class T>
inline int List<T>::getSize()
{
	return size;
}

template<class T>
inline void List<T>::clearList()
{
	if (head == nullptr)
	{
		std::cout << "The List is empty!" << std::endl;
		return;
	}
	this->~List();
	
}

template<class T>
inline bool List<T>::isEmpty()
{
	if (head == nullptr)
		return true;
	else
		return false;
}


template<class T>
inline bool List<T>::changeElem(int position, T object)
{
	Iterator* iter = new Iterator(this);
	int i = 0;
	do
	{
		if (i == position)
		{
			iter->cur->item = object;
			return true;
		}
		iter->next();
		i++;
	} while (i < size);
	return false;
}

template<class T>
inline T List<T>::findPos(int position)
{
	Iterator* iter = new Iterator(this);
	int i = 0;
	do
	{
		if (i == position)
			return iter->cur->item;
		iter->next();
		i++;
	} while (i < size);
	throw new IncorrectPosition;
}

template<class T>
inline bool List<T>::isVal(T object)
{
	Iterator* iter = new Iterator(this);
	int position = 0;
	do
	{
		if (iter->cur->item == object)
			return true;
		position++;
		iter->next();
	} while (position < size);
	return false;
}

template<class T>
inline List<T>::Node::Node()
{
	next = nullptr;
}


template<class T>
inline List<T>::Node::Node(T obj)
{
	item = obj;
	next = nullptr;
}


template<class T>
inline List<T>::Node::Node(const Node& source_node)
{
	item = source_node.item;
	next = source_node.next;
}

template<class T>
inline List<T>::Node::~Node()
{
	next = nullptr;
}

template<class T>
inline List<T>::Iterator::Iterator()
{
	ptr = nullptr;
	cur = nullptr;
	cur->item = NULL;
}

template<class T>
inline List<T>::Iterator::Iterator(List* sourceList)
{
	ptr = sourceList;
	cur = sourceList->head;
}

template<class T>
inline List<T>::Iterator::~Iterator()
{
	ptr = nullptr;
	delete cur;
}

template<class T>
inline bool List<T>::Iterator::first()
{
	if (ptr->head == nullptr)
		return false;
	cur = ptr->head;
	return true;
}

template<class T>
inline bool List<T>::Iterator::next()
{
	if (ptr->head == nullptr)
	{
		return false;
	}
	cur = cur->next;
	return true;
}

template<class T>
inline bool List<T>::Iterator::end()
{
	if (ptr->head == nullptr)
		return false;
	int k = ptr->size;
	while(--k > 0)
		next();
	return true;
}

template<class T>
inline bool List<T>::Iterator::isOff()
{
	if (cur == nullptr)
		return true;
	return false;
}

template<class T>
inline T& List<T>::Iterator::operator*()
{
	if (ptr->head == nullptr)
		throw new ListIsEmpty;
	else return cur->item;
}
	
