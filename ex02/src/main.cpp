#include <iostream>

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac != 2){
		std::cout << "Error: no input." << std::endl;
		return (1);
	}
	try {
		PmergeMe hell(av[1]);
	} catch (const std::string &e){
		std::cout << RED << e << RESET << std::endl;
	}

	return (0);
}
