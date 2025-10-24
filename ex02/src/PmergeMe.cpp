

#include "PmergeMe.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sstream>

std::ostream&	operator<<(std::ostream& os, const std::deque<size_t>& vec);
std::ostream&	operator<<(std::ostream& os, const std::vector<size_t>& vec);


PmergeMe::PmergeMe( void ) : _nb_of_nb(0), _Before("nothing.") {}
PmergeMe::~PmergeMe( void ) {}

PmergeMe::PmergeMe( const PmergeMe &other ) : _nb_of_nb(0), _Before("nothing.") {
	*this = other;
}

PmergeMe& PmergeMe::operator=(  const PmergeMe &other ){
	if (this != &other) {
		this->_start_vec = other._start_vec;
		this->_vec = other._vec;
		this->_end_vec = other._end_vec;
		this->_start_deq = other._start_deq;
		this->_deq = other._deq;
		this->_end_deq = other._end_deq;
	}
	return (*this);
}



PmergeMe::PmergeMe(int ac, char **av) : _start_vec(0), _end_vec(0), _start_deq(0), _end_deq(0), _nb_of_nb(ac - 1) , _Before("Before:\t" + this->_stock(ac, av)) {
	// (void)this->_nb_of_nb;
	if (!this->_sorted()) {
		this->_process_vector();
		this->_process_deque();
	}
	if (!this->_sorted()) {
		std::cerr << RED"KO!\n";
		return ;
	}
	// std::cout << "VECTOR: "	<< this->_vec<< "\n";
	// std::cout << "DEQUE: "	<< this->_deq<< "\n";

	this->_expected_print();
}

std::string		PmergeMe::_stock(int ac, char **av) {

	for (int i = 1; i < ac; i++)
	{
		std::stringstream ss(av[i]);
		size_t res = 0;
		ss >> res;
		if (res < 1 || ss.eof() == false || ss.fail())
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

void			PmergeMe::_expected_print( void ) {
	std::stringstream ss; ss << "Time To Process a range of " << this->_nb_of_nb << " elements with std::";

    // time duration
    double duration_vec = double(this->_end_vec - this->_start_vec) / CLOCKS_PER_SEC;
    double duration_deq = double((this->_end_deq - this->_start_deq)) / CLOCKS_PER_SEC;

	std::cout	<< this->_Before << "\n"
				<< "After:\t" << this->_vec << "\n"
				<< ss.str() << "vector<size_t> : " << duration_vec << "s\n"
				<< ss.str() << "deque<size_t> :  " << duration_deq << "s"
				<< std::endl;

}


template <typename Container>
static void			recursive_pair(Container &main, int level, Container &pend, Container &odd, Container &pend_cmp);

template <typename Container>
static void			iterative_pair(Container &main, int level, Container &pend, Container &odd, Container &pend_cmp);




bool					PmergeMe::_sorted( void ) {
	
	size_t last = 0;
	for (std::vector<size_t>::iterator it = this->_vec.begin(); it != this->_vec.end(); it++){
		if (*it < last)
			return false;
		last = *it;
	}
	return true;
}

void				PmergeMe::_process_vector( void ) {

	this->_start_vec = std::clock();
	std::vector<size_t> pend, odd, pend_cmp;

	recursive_pair(this->_vec, 1, pend, odd, pend_cmp);
	// iterative_pair(this->_vec, 1, pend, odd, pend_cmp);

	this->_end_vec = std::clock();
}




void				PmergeMe::_process_deque( void ) {
	this->_start_deq = std::clock();
	std::deque<size_t> pend, odd, pend_cmp;
	recursive_pair(this->_deq, 1, pend, odd, pend_cmp);
	// iterative_pair(this->_deq, 1, pend, odd, pend_cmp);


	this->_end_deq = std::clock();
}









template <typename Container>	static void			swap_for(Container &main, size_t index, size_t size_of_pair);

template <typename Container>	static Container	_jacobsthal_number(long n);

template <typename Container>	static int			binary_search(Container &array, size_t target, size_t index_max, size_t &size_of_pair );

template <typename Container>	static void			set_pend_cmp(Container &pend, Container &pend_cmp, size_t &size_of_pair );

template <typename Container>	static void			set_pend(Container &main, Container &pend, size_t &size_of_pair);

template <typename Container>	static void			clear_odd(Container &main, Container &odd);

template <typename Container>	static void			set_odd(Container &main, Container &odd, size_t index);

template <typename Container>	static void			print_by_size_of_pair(size_t size_of_pair, const Container &main, const Container &pend, const Container &odd);



/*recursive*/
template <typename Container>
static void			recursive_pair(Container &main, int level, Container &pend, Container &odd, Container &pend_cmp) {

	size_t size_of_pair = 1 << (level - 1);
	size_t nb_of_pair = (level == 1) ? ((main.size() / size_of_pair) >> 1) : (main.size() / size_of_pair) ;// a(x) b(x)

	// std::cout << YELLOW"size_of_pair: "<< size_of_pair<<"\n"RESET;
	// std::cout << YELLOW"nb_of_pair: "<< nb_of_pair<<"\n"RESET;
	// std::cout << GREEN"main.size():\t"<< main.size()<<RESET"\n";
	// print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main, pend, odd);

	size_t i = (size_of_pair << 1) - 1;
	while (i < main.size())
	{
		if (main[i - size_of_pair] > main[i]) {
			swap_for(main, i, size_of_pair);
		}
		i+= (size_of_pair << 1);
	}
	if (!((main.size() >> level) == 1 && level != 1)) { // down the recursive until cant be 2 pair
		recursive_pair(main, ++level, pend, odd, pend_cmp);
	}
	// exit of the recursive

	level--;

	// std::cout << YELLOW"main: "	<<	main	<<	"\n"RESET;
	if (main.size() != nb_of_pair * size_of_pair && level != 1) {
		set_odd(main, odd, (main.size() - (nb_of_pair * size_of_pair)));
	}
	set_pend(main, pend, size_of_pair);
	set_pend_cmp(pend, pend_cmp, size_of_pair);

	Container jacobsthal_number_index = _jacobsthal_number<Container>(pend_cmp.size() + 1);

	// print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main, pend, odd);

	// std::cout << PURPLE"pend_cmp: "	<<	pend_cmp	<<	"\npend_cmp.size(): "	<<	pend_cmp.size()	<<	"\n"RESET;
	// std::cout << BLUE"_jacobsthal_number: "	<<	jacobsthal_number_index	<<	"\n"RESET;
	// std::cout << BLUE"pend: "	<<	pend	<<	"\n"RESET;
	// std::cout << BLUE"odd: "	<<	odd		<<	"\n"RESET;

	size_t index_max = 0;
	for (size_t i = 0; i < jacobsthal_number_index.size(); i++)
	{
		if (index_max < jacobsthal_number_index[i] + i)
			index_max = jacobsthal_number_index[i] + i;
		int idx = binary_search(main, pend_cmp[jacobsthal_number_index[i]], index_max, size_of_pair);

		idx = ((idx == 0) ? (0) : (idx * size_of_pair));
		int pend_index = (jacobsthal_number_index[i] == 0)? (size_of_pair - 1) : ((jacobsthal_number_index[i] + 1) * size_of_pair - 1);
		for (size_t j = size_of_pair; j != 0; j--) {
			main.insert(main.begin() + idx, pend[pend_index--]);
		}
	}

	pend_cmp.clear();
	pend.clear();
	clear_odd(main, odd);

}

/*recursive*/




template <typename Container>
static void			iterative_pair(Container &main, int level, Container &pend, Container &odd, Container &pend_cmp) {

	while (1)
	{
		size_t size_of_pair = 1 << (level - 1);
		// size_t nb_of_pair = (level == 1) ? ((main.size() / size_of_pair) >> 1) : (main.size() / size_of_pair) ;// a(x) b(x)

		// std::cout << YELLOW"size_of_pair: "<< size_of_pair<<"\n"RESET;
		// std::cout << YELLOW"nb_of_pair: "<< nb_of_pair<<"\n"RESET;
		// std::cout << GREEN"main.size():\t"<< main.size()<<RESET"\n";
		// print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main, pend, odd);
		size_t i = (size_of_pair << 1) - 1;
		while (i < main.size())
		{
			if (main[i - size_of_pair] > main[i]) {
				swap_for(main, i, size_of_pair);
			}
			i+= (size_of_pair << 1);
		}
		if ((main.size() >> level) == 1 && level != 1)
			break;
		++level;
	}


	// exit of the recursive


	while (level) {
		level--;
		size_t size_of_pair = 1 << (level - 1);
		size_t nb_of_pair = (level == 1) ? ((main.size() / size_of_pair) >> 1) : (main.size() / size_of_pair) ;// a(x) b(x)

		if (main.size() != nb_of_pair * size_of_pair && level != 1) {
			set_odd(main, odd, (main.size() - (nb_of_pair * size_of_pair)));
		}
		set_pend(main, pend, size_of_pair);
		set_pend_cmp(pend, pend_cmp, size_of_pair);

		Container jacobsthal_number_index = _jacobsthal_number<Container>(pend_cmp.size() + 1);

		// print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main, pend, odd);

		// std::cout << PURPLE"pend_cmp: "	<<	pend_cmp	<<	"\npend_cmp.size(): "	<<	pend_cmp.size()	<<	"\n"RESET;
		// std::cout << BLUE"_jacobsthal_number: "	<<	jacobsthal_number_index	<<	"\n"RESET;
		// std::cout << BLUE"pend: "	<<	pend	<<	"\n"RESET;
		// std::cout << BLUE"odd: "	<<	odd		<<	"\n"RESET;

		size_t index_max = 0;
		for (size_t i = 0; i < jacobsthal_number_index.size(); i++)
		{
			if (index_max < jacobsthal_number_index[i] + i)
			index_max = jacobsthal_number_index[i] + i;
			int idx = binary_search(main, pend_cmp[jacobsthal_number_index[i]], index_max, size_of_pair);

			idx = ((idx == 0) ? (0) : (idx * size_of_pair));
			int pend_index = (jacobsthal_number_index[i] == 0)? (size_of_pair - 1) : ((jacobsthal_number_index[i] + 1) * size_of_pair - 1);
			for (size_t j = size_of_pair; j != 0; j--) {
				main.insert(main.begin() + idx, pend[pend_index--]);
			}
		}

		pend_cmp.clear();
		pend.clear();
		clear_odd(main, odd);

	}

}























template <typename Container>
static void			swap_for(Container &main, size_t index, size_t size_of_pair) {

	for (size_t j = index - size_of_pair; size_of_pair > 0 ; size_of_pair--)
	{
		int tmp = main[j];
		main[j--] = main[index];
		main[index--] = tmp;
	}
}



#include <cmath>
template <typename Container>
static Container	_jacobsthal_number(long n) {

	size_t i = 1, j = 1;
	long value = 0, last_value = 1;
	Container jacobsthal_number_index;
	do
	{
		value = round((pow(2, i + 1) + pow(-1, i)) / 3);
		// std::cout <<"value "<< value<< "\n";
		if (value > 1) {
			for (long v = value; v != last_value; v--){
				if (v <= n) {
					jacobsthal_number_index.push_back((v - 2)); // (j - 0) for the jacobsthal_number | (j - 1) for index start from (0(1 for the *) * size_of_pair) - 1 and tadoum the index pend_cmp)
					j++;
				}
			}
			last_value = value;
		}
		i++;
	} while (value < n);

	return (jacobsthal_number_index);
}


/* --- odd ---*/

template <typename Container>
static void			set_odd(Container &main, Container &odd, size_t index) {

	if (index > main.size())
		index = main.size();

	odd.insert(odd.end(), main.end() - index, main.end());
	main.erase(main.end() - index, main.end());
}

template <typename Container>
static void	clear_odd(Container &main, Container &odd){

	main.insert(main.end(), odd.begin(), odd.end());
	odd.clear();
}

/* --- odd ---*/

/* --- pend ---*/


template <typename Container>
static void			set_pend(Container &main, Container &pend, size_t &size_of_pair) {

	size_t	index;
	for (index = (size_of_pair << 1); index < main.size(); index+= size_of_pair)
	{
		typename Container::iterator start = main.begin() + index;
		pend.insert(pend.end(), start, start + size_of_pair);
		main.erase(start, start + size_of_pair);
	}
}

/* --- pend ---*/
//
/* --- pend_cmp ---*/

template <typename Container>
static void	set_pend_cmp(Container &pend, Container &pend_cmp, size_t &size_of_pair ) {
	for (size_t i = size_of_pair - 1; i < pend.size(); i+= size_of_pair) {
		pend_cmp.push_back(pend[i]);
	}
}

/* --- pend_cmp ---*/


template <typename Container>
static int			binary_search(Container &array, size_t target, size_t index_max, size_t &size_of_pair ) {
	size_t lower = 0, high = index_max + 1;

	while (high - lower > 1) {
		size_t mid = lower + (high - lower) / 2;

		size_t val = array[(mid == 0) ? (size_of_pair - 1) : (((mid + 1) * size_of_pair) - 1)];

		if (target > val) {
			lower = mid;
		} else {
			high = mid;
		}
	}

	if (lower == 0 && target < array[size_of_pair - 1]) {
		return (0);
	} else if (high == index_max && target < array[(index_max * size_of_pair) - 1]) {
		return (index_max);
	} else {
		if (target > array[((high + 1) * size_of_pair) - 1]) {
			return (high + 1);
		} else {
			return (high);
		}
	}
}
















template <typename Container>
static void			print_by_size_of_pair(size_t size_of_pair, const Container &main, const Container &pend, const Container &odd) {

	for (size_t i = 0; i + size_of_pair <= main.size(); i += size_of_pair) {
		std::cout << GREEN"[";
		for (size_t j = i; j < i + size_of_pair; j++) {
			if (j != i)
				std::cout << " ";
			std::cout << main[j];
		}
		std::cout << "] "RESET;
	}
	std::cout << "\n";
	(void)pend;(void)odd;
}

std::ostream&		operator<<(std::ostream& os, const std::vector<size_t>& vec)
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
std::ostream&		operator<<(std::ostream& os, const std::deque<size_t>& vec)
{
	if (vec.begin() == vec.end()) {
		os << "(null)";
		return os;
	}
	for (std::deque<size_t>::const_iterator vcit = vec.begin(); vcit != vec.end(); vcit++ ){
		os << *vcit;
		std::deque<size_t>::const_iterator next = vcit;
		++next;
		if (next != vec.end())
			os << "  ";// double space
	}
	os << " ";
	return os;
}
