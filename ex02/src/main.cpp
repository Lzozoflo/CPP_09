#include <iostream>

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2){
		std::cout << "Error: no input." << std::endl;
		return (1);
	}
	try {
		PmergeMe hell(ac, av);
	} catch (const std::string &e){
		std::cout << RED << e << RESET << std::endl;
	}

	return (0);
}


//11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7
