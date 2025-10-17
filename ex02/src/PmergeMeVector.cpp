

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


void			recursive_pair(std::vector<int> &main, int level, std::vector<int> &pend) {

	size_t size_of_pair = 1 << (level - 1);
	// std::cout << BLUE"size_of_pair:\t"<<size_of_pair<<RESET"\n";
	// size_t nb_of_pair = main.size() >> level;// a(x) b(x)
	// std::cout << BLUE"nb_of_pair:\t" << nb_of_pair <<RESET"\n";

	if ((main.size() >> level) == 0 && level != 1) { // when now pair of pair can be
		return;
	}

	// std::cout << YELLOW"main:\t"<< main<<RESET"\n";
	// if (level == 1) {
	// 	size_t i = (main.size() % 2 == 1) ? (main.size() - 1) : (main.size());

	// 	while (--i > 1)
	// 	{
	// 		// std::cout << YELLOW"["<< main[i]<<" "<< main[i - 1]<<"] "RESET;
	// 		if (main[i] < main[i - 1]){
	// 			int tmp = main[i];
	// 			main[i] = main[i - 1];
	// 			main[i - 1] = tmp;
	// 		}
	// 		i--;
	// 	}gm
	// 	// std::cout <<"\n";
	// }
	// else {
		size_t i = (size_of_pair << 1) - 1;

		while (i < main.size())
		{
			if (main[i - size_of_pair] > main[i]) {
				swap_for(main, i, size_of_pair);
			}
			i+= (size_of_pair << 1);
		}
	// }
	std::cout << YELLOW"main:\t"<< main<<RESET"\n";

	recursive_pair(main, ++level, pend);
}
