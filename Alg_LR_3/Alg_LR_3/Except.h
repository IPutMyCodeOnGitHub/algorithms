#include <conio.h>
#include <cstdlib>
#include <iostream>

//using namespace std;

class TreeError
{
public:
	virtual void Error() = 0;
};

class TreeIsEmpty : public TreeError
{
	void Error()
	{
		std::cout << "Exception" << std::endl;
		_getch();
	}
};

class IncorrectPosition : public TreeError
{
	void Error()
	{
		std::cout << "Exception" << std::endl;
		_getch();
	}
};
class IterOutside : public TreeError
{
	void Error()
	{
		std::cout << "Exception" << std::endl;
		_getch();
	}
};