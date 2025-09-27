#include <iostream>
// #include <vector>

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2){
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	try {
		BitcoinExchange btc;
		btc.output(av[1]);
	} catch (const std::string &e){
		std::cout << RED << e << RESET << std::endl;
	}

	return (0);
}
