

#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>


std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec);
void			recursive_pair(std::vector<int> &main, int level, std::vector<int> &pend, std::vector<int> &odd);
void			swap_for(std::vector<int> &main, size_t index, size_t size_of_pair);


void			PmergeMe::_process_vector( void ) {
	this->_start_vec = std::time(NULL);
	std::vector<int> pend;
	std::vector<int> odd;
	recursive_pair(this->_vec, 1, pend, odd);

	// std::cout << "pend: "<< pend << "\n";
	;
	this->_end_vec = std::time(NULL);
}

static void print_by_size_of_pair(size_t size_of_pair, const std::vector<int> &main, const std::vector<int> &pend, const std::vector<int> &odd) {

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


/* --- odd ---*/
void			set_odd(std::vector<int> &main, std::vector<int> &odd, size_t index, size_t &nb_of_pair, size_t &size_of_pair) {
	// std::cout << YELLOW"index: "<< index<<"\n"RESET;
	if (index > main.size())
		return;
	for (vec_iterator it = main.end() - index; it != main.end();)
	{
		odd.push_back(*it);
		it = main.erase(it);
	}
	if (nb_of_pair % 2 != 0) {
		vec_iterator start = main.end() - size_of_pair;
		odd.insert(odd.begin(), start, main.end());
		main.erase(start, main.end());
	}
}

void	clear_odd(std::vector<int> &main, std::vector<int> &odd){

	main.insert(main.end(), odd.begin(), odd.end());
	odd.erase(odd.begin(), odd.end());
}

/* --- odd ---*/


/* --- pend ---*/

void			set_pend(std::vector<int> &main, std::vector<int> &pend, size_t &size_of_pair) {

	(void)main;(void)pend;(void)size_of_pair;

	for (size_t index = (size_of_pair == 1) ? (size_of_pair) : (size_of_pair << 1); index < main.size(); index+= size_of_pair)
	{
		vec_iterator start = main.begin() + index;
		pend.insert(pend.end(), start, start + size_of_pair);
		main.erase(start, start + size_of_pair);
	}
}

void	clear_pend(std::vector<int> &main, std::vector<int> &pend) {

	main.insert(main.end(), pend.begin(), pend.end());
	pend.erase(pend.begin(), pend.end());


}

/* --- pend ---*/

void			recursive_pair(std::vector<int> &main, int level, std::vector<int> &pend, std::vector<int> &odd) {

	size_t size_of_pair = 1 << (level - 1);
	size_t nb_of_pair = (level == 1) ? ((main.size() / size_of_pair) >> 1) : (main.size() / size_of_pair) ;// a(x) b(x)

	// std::cout << YELLOW"size_of_pair: "<< size_of_pair<<"\n"RESET;
	// std::cout << YELLOW"nb_of_pair: "<< nb_of_pair<<"\n"RESET;
	// std::cout << GREEN"main.size():\t"<< main.size()<<RESET"\n";

	size_t i = (size_of_pair << 1) - 1;

	// print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main, pend, odd);
	while (i < main.size())
	{
		if (main[i - size_of_pair] > main[i]) {
			swap_for(main, i, size_of_pair);
		}
		i+= (size_of_pair << 1);
	}

	if (!((main.size() >> level) == 1 && level != 1)) { // when now pair of pair can be
		// std::cout << "recursive\n\n";
		recursive_pair(main, ++level, pend, odd);
	}
	level--;



	std::cout << YELLOW"main: "	<<	main	<<	"\n"RESET;
	if ((nb_of_pair % 2 != 0 || main.size() != nb_of_pair * size_of_pair) && level != 1) {
		set_odd(main, odd, (main.size() - (nb_of_pair * size_of_pair)), nb_of_pair, size_of_pair);
	}
	set_pend(main, pend, size_of_pair);


	clear_pend(main, pend);


	print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main, pend, odd);
	std::cout << BLUE"pend: "	<<	pend	<<	"\n"RESET;
	std::cout << BLUE"odd: "	<<	odd		<<	"\n"RESET;

	clear_odd(main, odd);


}










/*

11 2 17 0 16 8 6 15
 10 3 21 1 18 9 1 5
 3 5 89 9 9 99 14 19
 12 5 4 20 13 7


*/





void			swap_for(std::vector<int> &main, size_t index, size_t size_of_pair) {

	for (size_t j = index - size_of_pair; size_of_pair > 0 ; size_of_pair--)
	{
		int tmp = main[j];
		main[j--] = main[index];
		main[index--] = tmp;
	}
}
