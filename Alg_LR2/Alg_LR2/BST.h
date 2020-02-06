#pragma once
#include <iostream>
#include <stack>
#include <deque>
#include "Except.h"

template <class Data, class Key>
class Tree
{
public:
	class Node //вложенный класс элемента
	{
	public:
		Data data; //значение узла
		Key key; //ключ узла
		Node* left; //указатель на левого сына в списке
		Node* right; //указатель на правого сына в списке
		Node();
		Node(Data, Key);
		Node(const Node&);
		~Node();
	};
	Node* root;
	int size; //размер списка
	int operNum;

//public:
	Tree(); //конструктор списка по умолчанию +
	Tree(const Tree<Data, Key>&); //конструктор копирования +
	~Tree(); //деструктор списка +
	Node* copy(Node*);//функция копирования дерева +
	int getOperNum(); //опрос числа узлов дерева, просмотренных операцией +
	void privatShow(Node*, int); 
	void show(); //вывод структуры дерева на экран +
	bool push(Data data, Key key); //включение данных с заданнм ключом +
	bool deleteByKey(Key key); //удаление данных с заданным ключом +
	Data getData(Key key); //доступ к данным с заданным ключом +
	int getSize(); //опрос размера дерева +
	void clear(); //очистка дерева +
	bool empty(); //проверка дерева на пустоту +
	void round();//обход узлов дерева по cхеме Lt → t → Rt +
	int outLength(); //определение длины внешнего пути дерева (рекурсивная форма) +
	void privatOutLength(Node*, int, int*);
	Node* findPrevKey(Node* localRoot, Node* node); //поиск предыдущего узла
	Node* findNextKey(Node* localRoot, Node* node); //поиск следующего узла


	class Iterator //вложенный класс, выполняющий функции итератора
	{
	public:
		Tree* tree; //указатель на дерево
		Node* cur; //текущий узел дерева
		Iterator();
		Iterator(Tree<Data, Key>* tr);
		~Iterator();
		bool first(); //установка на первый  узел в дереве с  минимальным  ключом
		bool last(); //установка на  последний узел  в дереве  с максимальным ключом
		bool next(); //переход к следующему по значению ключа узлу в дереве
		bool prev(); //переход к предыдущему по значению ключа узлу в дереве
		bool isOff(); //проверка состояния итератора (внутри дерева/вне дерева)
		Data& operator*(); //доступ по чтению/записи к данным текущего узла в дереве
	};

	//friend class Iterator;
};

template<class Data, class Key>
inline Tree<Data, Key>::Node::Node()
{
	data = nullptr;
	key = nullptr;
	left = nullptr;
	right = nullptr;
}

template<class Data, class Key>
inline Tree<Data, Key>::Node::Node(Data d, Key k)
{
	data = d;
	key = k;
	left = nullptr;
	right = nullptr;
}

template<class Data, class Key>
inline Tree<Data, Key>::Node::Node(const Node& n)
{
	key = n.key;
	data = n.data;
	left = n.left;
	right = n.right;
}

template<class Data, class Key>
inline Tree<Data, Key>::Node::~Node()
{
	if (left != nullptr) left = nullptr;
	if (right != nullptr) right = nullptr;
	//обойти дерево и занулить все указатели
}

template<class Data, class Key>
inline Tree<Data, Key>::Tree()
{
	root = nullptr;
	size = 0;
}

template<class Data, class Key>
inline typename Tree<Data, Key>::Node* Tree<Data, Key>::copy(Node* tmp)
{
	if (tmp == nullptr)
		return NULL;

	if (root == nullptr)
	{
		root = new Node(*tmp);
		if (tmp->left != nullptr)
			root->left = copy(tmp->left);
		if (tmp->right != nullptr)
			root->right = copy(tmp->right);
		return root;
	}

	Node *newRoot = new Node(*tmp);
	if (tmp->left != nullptr)
		newRoot->left = copy(tmp->left);
	if (tmp->right != nullptr)
		newRoot->right = copy(tmp->right);
	return newRoot;
		
}

template<class Data, class Key>
inline Tree<Data, Key>::Tree(const Tree<Data, Key>& tree)
{
	root = nullptr;
	size = tree.size;
	copy(tree.root);
}

template<class Data, class Key>
inline Tree<Data, Key>::~Tree()
{
	clear();
}

template<class Data, class Key>
inline int Tree<Data, Key>::getOperNum()
{
	return operNum;
}

template<class Data, class Key>
inline void Tree<Data, Key>::privatShow(Node* tmp, int level)
{
	if (tmp == NULL)
		return;
	privatShow(tmp->right, level + 1);
	for (int i = 0; i < 5 * level; i++)
		std::cout << " ";
	std::cout << tmp->key << "|" << tmp->data  << std::endl;
	privatShow(tmp->left, level + 1);

	/*if (root == nullptr)
		throw new TreeIsEmpty;

	std::deque<Node*> deq;
	deq.push_back(root);
	Node* tmp;
	int level = 1;

	
	while (!deq.empty())
	{
		tmp = deq.front();
		if (tmp->left != nullptr)
			deq.push_back(tmp->left);
		if (tmp->right != nullptr)
			deq.push_back(tmp->right);
		
		std::cout << tmp->key << " ";
		deq.pop_front();
	}*/
}

template<class Data, class Key>
inline void Tree<Data, Key>::show()
{
	int level = 1;
	privatShow(root, level);
}

template<class Data, class Key>
inline bool Tree<Data, Key>::push(Data data, Key key)
{
	operNum = 0;
	if (root == nullptr)
	{
		root = new Node(data, key);
		size++;
		operNum++;
		return true;
	}

	Node* tmp = root;
	Node* pred = nullptr;
	while (tmp != nullptr)
	{
		pred = tmp;
		if (key == tmp->key)
			return false;
		if (key < tmp->key)
			tmp = tmp->left;
		else 
			tmp = tmp->right;
		operNum++;
	}
	if (key < pred->key)
		pred->left = new Node(data, key);
	else
		pred->right = new Node(data, key);

	size++;
	return true;
}

template<class Data, class Key>
inline bool Tree<Data, Key>::deleteByKey(Key key)
{
	operNum = 0;
	Node* tmp = root;
	Node* pred = nullptr;
	while (tmp != nullptr && tmp->key != key)
	{
		pred = tmp;
		if (key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
		operNum++;
	}
	if (tmp == nullptr)
		return false;

	Node* tmp0 = nullptr;
	Node* x = nullptr;
	if (tmp->left != nullptr && tmp->right != nullptr)
	{
		tmp0 = tmp;
		pred = tmp;
		tmp = tmp->right;
		while (tmp->left != nullptr)
		{
			pred = tmp;
			tmp = tmp->left;
			operNum++;
		}
		x = tmp->right;
	}
	else 
	{
		tmp0 = nullptr;
		if (tmp->left == nullptr && tmp->right == nullptr)
			x = nullptr;
		if (tmp->left == nullptr)
			x = tmp->right;
		if (tmp->right == nullptr)
			x = tmp->left;
	}
	if (pred == nullptr)
		root = x;
	else 
		if (tmp->key < pred->key)
			pred->left = x;
		else pred->right = x;
	if (tmp0 != nullptr)
	{
		tmp0->key = tmp->key;
		tmp0->data = tmp->data;
	}
	delete tmp;
	size--;
	return true;
}

template<class Data, class Key>
inline Data Tree<Data, Key>::getData(Key key)
{
	Node* tmp = root;
	operNum = 0;
	while (tmp != nullptr && key != tmp->key)
	{
		if (key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
		operNum++;
	}
	if (tmp == nullptr)
		throw new IncorrectPosition;

	return tmp->data;
}

template<class Data, class Key>

inline int Tree<Data, Key>::getSize()
{
	return size;
}

template<class Data, class Key>
inline void Tree<Data, Key>::clear()
{
	std::deque<Node*> deq;
	deq.push_back(root);
	Node* tmp;
	int level = 1;

	while (!deq.empty())
	{
		tmp = deq.front();
		if (tmp->left != nullptr)
			deq.push_back(tmp->left);
		if (tmp->right != nullptr)
			deq.push_back(tmp->right);
		tmp->left = nullptr;
		tmp->right = nullptr;
		deq.pop_front();
	}
	root = nullptr;
	size = 0;
}

template<class Data, class Key>
inline bool Tree<Data, Key>::empty()
{
	if (root == nullptr)
		return true;
	else return false;
}

template<class Data, class Key>
inline void Tree<Data, Key>::round()
{
	std::stack <Node*> s1, s2, s3;
	s1.push(root);
	Node* tmp;
	while (!s1.empty() || !s2.empty())
	{
		if (!s1.empty())
		{
			tmp = s1.top();
			s1.pop();
			s2.push(tmp);
			if (tmp->left != nullptr)
				s1.push(tmp->left);
		}
		else
		{
			tmp = s2.top();
			s2.pop();
			s3.push(tmp);
			if (tmp->right != nullptr)
				s1.push(tmp->right);
		}
		while (!s3.empty())
		{
			tmp = s3.top();
			s3.pop();
			std::cout << tmp->key << " ";
		}
	}
	std::cout << std::endl;
}

template<class Data, class Key>
inline void Tree<Data, Key>::privatOutLength(Node* tmp, int length, int* outLen)
{
	if (tmp->left == nullptr || tmp->right == nullptr)
	{
		*outLen += length;
	}
	if (tmp->left != nullptr)
		privatOutLength(tmp->left, length + 1, outLen);
	
	if (tmp->right != nullptr)
		privatOutLength(tmp->right, length + 1, outLen);
	
	else return;
}

template<class Data, class Key>
inline int Tree<Data, Key>::outLength()
{
	int outLen = 0;
	if (root == nullptr)
		throw new TreeIsEmpty;
	privatOutLength(root, 0, &outLen);

	return outLen;
}

template<class Data, class Key>
typename Tree<Data, Key>::Node* Tree<Data, Key>::findPrevKey(Node *localRoot, Node *node)
{
	if (localRoot == node || localRoot == NULL)
		return NULL;
	if (node->key > localRoot->key)
	{
		Node *tmp = findPrevKey(localRoot->right, node);
		if (tmp != NULL)
			return tmp;
		else
			return localRoot;
	}
	else
		return findPrevKey(localRoot->left, node);
}

template<class Data, class Key>
typename Tree<Data, Key>::Node* Tree<Data, Key>::findNextKey(Node *localRoot, Node *node)
{
	if (localRoot == node || localRoot == nullptr)
		return nullptr;
	if (node->key < localRoot->key)
	{
		Node *tmp = findNextKey(localRoot->left, node);
		if (tmp != nullptr)
			return tmp;
		else
			return localRoot;
	}
	else
		return findNextKey(localRoot->right, node);
}

/*template<class Data, class Key>
typename Tree<Data, Key>::Node* Tree<Data, Key>::copy(Node *root)
{
	if (root == nullptr)
		return nullptr;
	Node *newRoot = new Node(root->data, root->key);
	newRoot->left = copy(newRoot->left);
	newRoot->right = copy(newRoot->right);
	return newRoot;
}*/

template<class Data, class Key>
inline Tree<Data, Key>::Iterator::Iterator()
{
	tree = nullptr;
	cur = nullptr;
}

template<class Data, class Key>
inline Tree<Data, Key>::Iterator::Iterator(Tree<Data, Key>* tr)
{
	tree = tr;
	cur = tr->root;
}

template<class Data, class Key>
inline Tree<Data, Key>::Iterator::~Iterator()
{
	tree = nullptr;
	cur = nullptr;
}

template<class Data, class Key>
inline bool Tree<Data, Key>::Iterator::first()
{
	if (tree->root == nullptr)
		return false;
	else
	{
		cur = tree->root;
		while (cur->left != nullptr)
			cur = cur->left;
		return true;
	}
}

template<class Data, class Key>
inline bool Tree<Data, Key>::Iterator::last()
{
	if (tree->root == nullptr)
		return false;
	else
	{
		cur = tree->root;
		while (cur->right != nullptr)
			cur = cur->right;
		return true;
	}
}

template<class Data, class Key>
inline bool Tree<Data, Key>::Iterator::prev()
{
	if (tree->root == nullptr || cur == nullptr)
		return false;
	std::cout << "cur key = " << cur->key << std::endl;
	if (cur->left == nullptr)
		cur = tree->findPrevKey(tree->root, cur);
	else
	{
		cur = cur->left;
		while (cur->right != nullptr)
			cur = cur->right;
	}
	return true;
}

template<class Data, class Key>
inline bool Tree<Data, Key>::Iterator::next()
{
	if (tree->root == nullptr || cur == nullptr)
		return false;
	if (cur->right == nullptr)
		cur = tree->findNextKey(tree->root, cur);
	else
	{
		cur = cur->right;
		while (cur->left != nullptr)
			cur = cur->left;
	}
	return true;
	std::cout << "key = " << cur->key << std::endl;
}

template<class Data, class Key>
inline bool Tree<Data, Key>::Iterator::isOff()
{
	if (cur == nullptr)
		return true;
	else
		return false;
}

template<class Data, class Key>
inline Data& Tree<Data, Key>::Iterator::operator*()
{
	if (cur == nullptr)
		throw new IterOutside;
	else
		return cur->data;
}
