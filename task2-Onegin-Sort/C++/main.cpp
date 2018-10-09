#include "OneginSort.hpp"

#include <iostream> // std::cerr
#include <cstdlib>  // system

int main()
{
	std::ios_base::sync_with_stdio(false);

	try
	{
		std::cout << "Enter path:" << std::endl;

		std::filesystem::path path;
		std::cin >> path;
		 
		auto text = ReadFile(path);

		auto text4tts = text;
		TowardTextSort(text4tts);
		// On a non-POSIX system, it is possible that p.stem()+p.extension() != p.filename() even though generic-format versions are the same.
		if (!Write2File(std::filesystem::path(path).replace_filename(path.stem().concat("_toward").concat(path.extension().c_str())), text4tts))
		{
			std::cerr << "Cannot write to file\n";

			return 1;
		}

		BackwardTextSort(text);
		// On a non-POSIX system, it is possible that p.stem()+p.extension() != p.filename() even though generic-format versions are the same.
		if (!Write2File(path.replace_filename(path.stem().concat("_backward").concat(path.extension().c_str())), text))
		{
			std::cerr << "Cannot write to file\n";

			return 1;
		}
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