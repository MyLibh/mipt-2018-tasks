#include "SquareSolver.hpp"

#include <iostream> // std::cerr
#include <cstdlib>  // system

int main()
{
	std::ios_base::sync_with_stdio(false);

	try
	{
		std::cout << "Enter coefs:" << std::endl;

		ld_t a{},
			 b{},
			 c{};
		std::cin >> a >> b >> c;
		
		std::cout << "Solving: " << a << "x^2 + " << b << "x + " << c << " = 0" << std::endl;

		const auto roots = SolveSquare(a, b, c);
		PrintQuadResults(roots);
	}
	catch (std::ios_base::failure &f)
	{
		std::cerr << f.what();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unhandled exception" << std::endl;
	}

	system("pause");
	return 0;
}