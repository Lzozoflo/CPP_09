

#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>


std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec);
void			recursive_pair(std::vector<int> &main, int level, std::vector<int> &pend);


void			PmergeMe::_process_vector( void ) {
	this->_start_vec = std::time(NULL);
	std::vector<int> pend;
	recursive_pair(this->_vec, 1, pend);

	// std::cout << "pend: "<< pend << "\n";



	;
	this->_end_vec = std::time(NULL);
}

void			swap_for(std::vector<int> &main, size_t index, size_t size_of_pair){

	for (size_t j = index - size_of_pair; size_of_pair > 0 ; size_of_pair--)
	{
		int tmp = main[j];
		main[j--] = main[index];
		main[index--] = tmp;
	}
}
static void print_by_size_of_pair(size_t size_of_pair, const std::vector<int> &main) {
	for (size_t i = 0; i + size_of_pair <= main.size(); i += size_of_pair) {
		std::cout << GREEN"[";
		for (size_t j = i; j < i + size_of_pair; j++) {
			if (j != i)
				std::cout << " ";
			std::cout << main[j];
		}
		std::cout << "] "RESET;
	}
	std::cout << "\n\n";
}


void			recursive_pair(std::vector<int> &main, int level, std::vector<int> &pend) {

	size_t size_of_pair = 1 << (level - 1);
	// std::cout << BLUE"size_of_pair: "<< size_of_pair<<"\n"RESET;
	size_t i = (size_of_pair << 1) - 1;

	print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main);
	while (i < main.size())
	{
		if (main[i - size_of_pair] > main[i]) {
			swap_for(main, i, size_of_pair);
		}
		i+= (size_of_pair << 1);
	}
	// std::cout << GREEN"main:\t"<< main<<RESET"\n";

	if (!((main.size() >> level) == 1 && level != 1)) { // when now pair of pair can be
		recursive_pair(main, ++level, pend);
	}
	// else {
	// 	print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main);
	// }

}
