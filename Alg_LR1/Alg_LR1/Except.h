#include <conio.h>
#include <cstdlib>
#include <iostream>

//using namespace std;

class ListError
{
public:
	virtual void Error() = 0;
};

class ListIsEmpty : public ListError
{
	void Error()
	{
		std::cout << "Exception" << std::endl;
		_getch();
	}
};

class IncorrectPosition : public ListError
{
	void Error()
	{
		std::cout << "Exception" << std::endl;
		_getch();
	}
};