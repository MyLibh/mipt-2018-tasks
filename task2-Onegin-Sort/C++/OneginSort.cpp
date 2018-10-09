#include "OneginSort.hpp" 

#include <algorithm> // std::sort, std::lexicographical_compare
#include <execution> 
#include <filesystem>
#include <fstream> 
#include <iostream>  // std::cerr

text_t ReadFile(const std::filesystem::path &crPath)
{
	std::ifstream file(crPath);
	if (!file.is_open())
	{
		std::cerr << "Cannot read the file\n";

		return { };
	}

	text_t result;
	while (!file.eof())
	{
		line_t tmp;
		std::getline(file, tmp);

		result.push_back(tmp);
	}

	file.close();
	
	return result;
}

bool Write2File(const std::filesystem::path &crPath, const text_t &crText)
{
	std::ofstream file(crPath);
	if (!file.is_open())
		return false;

	for (auto &&line : crText)
		file << line << std::endl;

	file.close();

	return true;
}

void TowardTextSort(text_t &rText) // Not the best solution
{
	static auto comp = [](auto str1, auto str2) 
	{ 
		return std::lexicographical_compare(std::execution::par_unseq, std::begin(str1), std::end(str1), std::begin(str2), std::end(str2)); 
	};

	std::sort(std::execution::par_unseq, std::begin(rText), std::end(rText), comp);
}

void BackwardTextSort(text_t &rText) // Not the best solution
{
	static auto comp = [](auto str1, auto str2) 
	{ 
		return std::lexicographical_compare(std::execution::par_unseq, std::rbegin(str1), std::rend(str1), std::rbegin(str2), std::rend(str2)); 
	};

	std::sort(std::execution::par_unseq, std::begin(rText), std::end(rText), comp);
}
