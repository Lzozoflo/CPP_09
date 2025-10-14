#include "PmergeMe.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sstream>

PmergeMe::PmergeMe( void ) : _nb_of_nb(0) {}
PmergeMe::~PmergeMe( void ) {}

// PmergeMe &PmergeMe::operator=( const PmergeMe &other ) {
// 	if (this != &other) {
// 		;
// 		// this
// 	}
// 	return (*this);
// }

PmergeMe::PmergeMe(int ac, char **av) : _nb_of_nb(ac - 1) {
	this->_stock(ac, av);
	(void)ac;
	(void)av;
	(void)this->_nb_of_nb;
}


void	PmergeMe::_debug_print( void ) {

	std::ostringstream oss;

	oss << YELLOW"VECTOR:"RESET;

	vec_iterator v_it = this->_vec.begin();
	while(v_it != this->_vec.end()) {
		oss << " " << (*v_it)++;
	}

	oss << "\n" << YELLOW"DEQUE:"RESET;

	deq_iterator d_it = this->_deq.begin();
	while(d_it != this->_deq.end()) {
		oss << " " << (*d_it)++;
	}
	oss << "\n";
	std::cout << oss.str() << std::endl;
}


void PmergeMe::_stock(int ac, char **av) {

	for (int i = 1; i < ac; i++)
	{
		std::stringstream ss(av[i]);
		int res = 0;
		ss >> res;
		if (av[i][0] == '-' || ss.eof() == false || ss.fail())
			throw (std::string("Error"));
		this->_vec.push_back(res);
		this->_deq.push_back(res);
	}
}

void	PmergeMe::_expected_print() {

}
