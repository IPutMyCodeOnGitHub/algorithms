#include "BST.h"

template <class Data, class Key>
class NewTree : Tree<Data,Key>
{
public:
	class newNode : Tree<Data,Key>::Node
	{
		int balance;
	};
	
	class newIterator : Tree<Data,Key>::Iterator
	{
	public:
		newIterator(NewTree<Data, Key>*) : Iterator() {};
		int setBal(int);
	};
	
};



template<class Data, class Key>
inline int NewTree<Data, Key>::newIterator::setBal(int a)
{
	cur->balance = a;
	return cur->balance;
}
