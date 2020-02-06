
#include "BST.h"

template <class Data, class Key>
class BalanceTree : public Tree<Data, Key>
{
	class Node : public Tree<Data, Key>::Node //вложенный класс узла
	{
	public:
		int height;
		Node() {
			Tree<Data, Key>::Node::Node();
			height = 0;
		}
	};

	int height(Node*);
	int bfactor(Node*);
	void fixheight(Node*);
	Node* rotateright(Node*);
	Node* rotateleft(Node*);
	Node* balance(Node* p);
	Node* privatePush(Node*, Data, Key);

public:
	bool push(Data dat, Key k);
	
};


template<class Data, class Key>
inline int BalanceTree<Data, Key>::height(Node* p)
{
	return p ? p->height : 0;
}

template<class Data, class Key>
inline int BalanceTree<Data, Key>::bfactor(Node* p)
{
	return height(p->right) - height(p->left);
}

template<class Data, class Key>
inline void BalanceTree<Data, Key>::fixheight(Node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

template<class Data, class Key>
inline typename BalanceTree<Data, Key>::Node* BalanceTree<Data, Key>::rotateright(Node* p) // правый поворот вокруг p
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

template<class Data, class Key>
inline typename BalanceTree<Data, Key>::Node* BalanceTree<Data, Key>::rotateleft(Node* q) // левый поворот вокруг q
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

template<class Data, class Key>
inline typename BalanceTree<Data, Key>::Node* BalanceTree<Data, Key>::balance(Node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

template<class Data, class Key>
inline bool BalanceTree<Data, Key>::push(Data data, Key key) {

	int prevSize = size;
	root = privatePush(root, data, key);
	return prevSize != size ? 1 : 0;
}

template<class Data, class Key>
inline typename BalanceTree<Data, Key>::Node* BalanceTree<Data, Key>::privatePush(Node* root, Data data, Key key) {
	if (root != nullptr)
	{
		if (root->key == key)
			return;
		if (key < root->key)
			root->left = privatePush(root->left, data, key);
		else
			root->right = privatePush(root->right, data, key);

		return balance(root);
	}
	else return new Node(data, key);
}