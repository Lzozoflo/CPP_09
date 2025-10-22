

#include "PmergeMe.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec);

PmergeMe::PmergeMe( void ) : _nb_of_nb(0)  {}
PmergeMe::~PmergeMe( void ) {}

// PmergeMe &PmergeMe::operator=( const PmergeMe &other ) {
// 	if (this != &other) {
// 		;
// 		// this
// 	}
// 	return (*this);
// }

PmergeMe::PmergeMe(int ac, char **av) : _nb_of_nb(ac - 1) , _Before("Before:\t" + this->_stock(ac, av)) {
	// (void)this->_nb_of_nb;
	this->_process_vector();
	this->_process_deque();
	this->_expected_print();
}




std::string		PmergeMe::_stock(int ac, char **av) {

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
	std::stringstream ss("");
	for (vec_iterator vit = this->_vec.begin(); vit != this->_vec.end(); vit++ ){
		ss << *vit << "  ";// double space
	}
	return (ss.str());
}


void			PmergeMe::_debug_print( void ) {

	std::stringstream ss;

	ss << YELLOW"VECTOR:"RESET;

	vec_iterator v_it = this->_vec.begin();
	while(v_it != this->_vec.end()) {
		ss << " " << (*v_it)++;
	}

	ss << "\n" << YELLOW"DEQUE:"RESET;

	deq_iterator d_it = this->_deq.begin();
	while(d_it != this->_deq.end()) {
		ss << " " << (*d_it)++;
	}
	ss << "\n";
	std::cout << ss.str() << std::endl;
}

void			PmergeMe::_expected_print( void ) {
	std::stringstream ss; ss << "Time To Process a range of " << this->_nb_of_nb << " elements with std::";

	std::cout	<< this->_Before << "\n"
				<< "After:\t" << this->_vec << "\n"
				<< ss.str() << "vector<int> : " << (this->_end_vec - this->_start_vec) << "\n"
				<< ss.str() << "deque<int> : " << (this->_end_deq - this->_start_deq)
				<< std::endl;

}







































std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
{
	if (vec.begin() == vec.end()) {
		os << "(null)";
		return os;
	}
	for (vec_const_iterator vcit = vec.begin(); vcit != vec.end(); vcit++ ){
		os << *vcit;
		std::vector<int>::const_iterator next = vcit;
		++next;
		if (next != vec.end())
			os << "  ";// double space
	}
	os << " ";
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<size_t>& vec)
{
	if (vec.begin() == vec.end()) {
		os << "(null)";
		return os;
	}
	for (std::vector<size_t>::const_iterator vcit = vec.begin(); vcit != vec.end(); vcit++ ){
		os << *vcit;
		std::vector<size_t>::const_iterator next = vcit;
		++next;
		if (next != vec.end())
			os << "  ";// double space
	}
	os << " ";
	return os;
}
