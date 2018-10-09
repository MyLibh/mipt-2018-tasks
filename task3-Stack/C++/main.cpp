#include "Stack.hpp"

#include <iostream> // std::cout, std::cerr

using namespace NStack;

int main()
{
	try
	{
		Stack<> stack;
		stack.push(353);
		stack.dump(std::cout);
	}
	catch (...)
	{
		std::cerr << "Unhandled exception" << std::endl;
	}

	system("pause");
	return 0;
}