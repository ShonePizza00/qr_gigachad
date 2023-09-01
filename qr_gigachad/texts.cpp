#include "texts.h"

void texts::printStrGetChoice(const std::string& str, int& dest)
{
	std::cout << str << '\n' << texts::choiceStr;
	std::cin >> dest;
	std::cout << std::endl;
	return;
}

void texts::printStrGetChoice(const std::string& str, std::string& dest)
{
	std::cout << str << '\n' << texts::choiceStr;
	std::cin >> dest;
	std::cout << std::endl;
	return;
}