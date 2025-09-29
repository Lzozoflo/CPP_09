#include <iostream>

#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2){
		std::cout << "Error: no input." << std::endl;
		return (1);
	}
	try {
		RPN ReversePolishNotation(av[1]);
	} catch (const std::string &e){
		std::cout << RED << e << RESET << std::endl;
	}

	return (0);
}
