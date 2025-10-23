

#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>


std::ostream&	operator<<(std::ostream& os, const std::vector<int>& vec);
std::ostream&	operator<<(std::ostream& os, const std::vector<size_t>& vec);
void			recursive_pair(std::vector<int> &main, int level, std::vector<int> &pend, std::vector<int> &odd, std::vector<int> &main_cmp, std::vector<int> &pend_cmp);
void			swap_for(std::vector<int> &main, size_t index, size_t size_of_pair);


void			PmergeMe::_process_vector( void ) {
	this->_start_vec = std::time(NULL);
	std::vector<int> pend, odd;
	std::vector<int> pend_cmp, main_cmp;
	recursive_pair(this->_vec, 1, pend, odd, main_cmp, pend_cmp);

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

#include <cmath>
std::vector<size_t> _jacobsthal_number(long n) {

	size_t i = 1, j = 1;
	long value = 0, last_value = 1;
	std::vector<size_t> jacobsthal_number_index;
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

void			set_odd(std::vector<int> &main, std::vector<int> &odd, size_t index) {

	if (index > main.size())
		index = main.size();

	odd.insert(odd.end(), main.end() - index, main.end());
	main.erase(main.end() - index, main.end());
}

void	clear_odd(std::vector<int> &main, std::vector<int> &odd){

	main.insert(main.end(), odd.begin(), odd.end());
	odd.clear();
}

/* --- odd ---*/

/* --- pend ---*/

void			set_pend(std::vector<int> &main, std::vector<int> &pend, size_t &size_of_pair) {

	size_t	index;
	for (index = (size_of_pair << 1); index < main.size(); index+= size_of_pair)
	{
		vec_iterator start = main.begin() + index;
		pend.insert(pend.end(), start, start + size_of_pair);
		main.erase(start, start + size_of_pair);
	}
	// index -=
	// if ()
}

/* --- pend ---*/









// void	clear_pend(std::vector<int> &main, std::vector<int> &odd){
// 	main.insert(main.end(), odd.begin(), odd.end());
// 	odd.clear();
// }



/* --- pend_cmp ---*/

void	set_pend_cmp(std::vector<int> &pend, std::vector<int> &pend_cmp, size_t &size_of_pair ) {
	for (size_t i = size_of_pair - 1; i < pend.size(); i+= size_of_pair) {
		pend_cmp.push_back(pend[i]);
	}
}
void	set_main_cmp(std::vector<int> &main, std::vector<int> &main_cmp, size_t &size_of_pair ) {
	for (size_t i = size_of_pair - 1; i < main.size(); i+= size_of_pair) {
		main_cmp.push_back(main[i]);
	}
}

/* --- pend_cmp ---*/




static int binary_search(std::vector<int> &array, int target, size_t index_max) {
	size_t lower = 0, high = index_max + 1;

	std::cout << BLUE"\narray: "	<<	array	<<	"\n"RESET;
	std::cout << "index_max: " << index_max<< "\n";
	std::cout << "target: "<< target<< "\n";
	while (high - lower > 1) {
		size_t mid = lower + (high - lower) / 2;

		int val = array[mid];

		std::cout << "val: "<< val<< "\n";
		if (target > val) {
			lower = mid;
		} else {
			high = mid;
		}
	}

	std::cout << "lower: "<< lower<< "\n";
	std::cout << "high: "<< high<< "\n";

	if (lower == 0 && target < array[0]) {
		std::cout << "return (0);\n";
		return (0);
	} else if (high == index_max && target < array[index_max]) {
		std::cout << "return (index_max);\n";
		return (index_max);
	} else {
		std::cout << "array[high]: "<< array[high]<< "\n";
		if (target > array[high]) {
			std::cout << "return (high + 1);\n";
			return (high + 1);
		} else {
			std::cout << "return (high);\n";
			return (high);
		}
	}
}


void			recursive_pair(std::vector<int> &main, int level, std::vector<int> &pend, std::vector<int> &odd, std::vector<int> &main_cmp, std::vector<int> &pend_cmp) {

	size_t size_of_pair = 1 << (level - 1);
	size_t nb_of_pair = (level == 1) ? ((main.size() / size_of_pair) >> 1) : (main.size() / size_of_pair) ;// a(x) b(x)

	// std::cout << YELLOW"size_of_pair: "<< size_of_pair<<"\n"RESET;
	// std::cout << YELLOW"nb_of_pair: "<< nb_of_pair<<"\n"RESET;
	// std::cout << GREEN"main.size():\t"<< main.size()<<RESET"\n";
	print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main, pend, odd);

	size_t i = (size_of_pair << 1) - 1;
	while (i < main.size())
	{
		if (main[i - size_of_pair] > main[i]) {
			swap_for(main, i, size_of_pair);
		}
		i+= (size_of_pair << 1);
	}
	if (!((main.size() >> level) == 1 && level != 1)) { // down the recursive until cant be 2 pair
		recursive_pair(main, ++level, pend, odd, main_cmp, pend_cmp);
	}
	// exit of the recursive


	level--;

	std::cout << YELLOW"main: "	<<	main	<<	"\n"RESET;
	if (main.size() != nb_of_pair * size_of_pair && level != 1) {
		set_odd(main, odd, (main.size() - (nb_of_pair * size_of_pair)));
	}
	set_pend(main, pend, size_of_pair);
	set_pend_cmp(pend, pend_cmp, size_of_pair);
	std::vector<size_t> jacobsthal_number_index = _jacobsthal_number(pend_cmp.size() + 1);


	print_by_size_of_pair((level == 1) ? (size_of_pair + 1) : (size_of_pair), main, pend, odd);
	// std::cout << PURPLE"main_cmp: "	<<	main_cmp	<<	"\nmain_cmp.size(): "	<<	main_cmp.size()	<<	"\n"RESET;
	// std::cout << PURPLE"pend_cmp: "	<<	pend_cmp	<<	"\npend_cmp.size(): "	<<	pend_cmp.size()	<<	"\n"RESET;
	// std::cout << BLUE"_jacobsthal_number: "	<<	jacobsthal_number_index	<<	"\n"RESET;
	std::cout << BLUE"pend: "	<<	pend	<<	"\n"RESET;
	std::cout << BLUE"odd: "	<<	odd		<<	"\n"RESET;


	size_t index_max = 0;
	for (size_t i = 0; i < jacobsthal_number_index.size(); i++)
	{
		set_main_cmp(main, main_cmp, size_of_pair);
		if (index_max < jacobsthal_number_index[i] + i)
			index_max = jacobsthal_number_index[i] + i;
		int idx = binary_search(main_cmp, pend_cmp[jacobsthal_number_index[i]], index_max);
		std::cout << "idx: " << idx<< "\n";
		idx = ((idx == 0) ? (0) : (idx * size_of_pair));

		int pend_index = (jacobsthal_number_index[i] == 0)? (size_of_pair - 1) : ((jacobsthal_number_index[i] + 1) * size_of_pair - 1);
		for (size_t j = size_of_pair; j != 0; j--) {
			main.insert(main.begin() + idx, pend[pend_index--]);
		}
		main_cmp.clear();
	}

	// std::cout << BLACK"main: "	<<	main	<<	"\n"RESET;



	pend_cmp.clear();
	main_cmp.clear();
	pend.clear();
	clear_odd(main, odd);


}




// 	binary_insert(main, pend, size_of_pair, _jacobsthal_number(((pend.size()) ? (pend.size() / size_of_pair): (0)) + 1));

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



// 	binary_insert(main, pend, size_of_pair, _jacobsthal_number(((pend.size()) ? (pend.size() / size_of_pair): (0)) + 1));
// void	binary_insert(std::vector<int> &main, std::vector<int> &pend, size_t &size_of_pair, std::vector<size_t> jacobsthal_number_index) {

// 	// std::cout << "to_cmp: ";
// 	if (jacobsthal_number_index.size() == 0)
// 		return;
// 	size_t index_max = 0;
// 	for (size_t i = 0; i < jacobsthal_number_index.size(); i++)
// 	{
// 		if (index_max < jacobsthal_number_index[i])
// 			index_max = jacobsthal_number_index[i];
// 		int idx = upperBoundBlock(main, pend[jacobsthal_number_index[i] * size_of_pair - 1], index_max, size_of_pair);
// 		idx = ((idx == 0) ? (0) : (idx + 1));
// 		int pend_index = (jacobsthal_number_index[i] * size_of_pair - 1);
// 		for (size_t j = size_of_pair; j != 0; j--) {
// 			main.insert(main.begin() + idx, pend[pend_index--]);
// 		}
// 		std::cout	<< "\nsize_of_pair: "	<<	size_of_pair << "\n";
// 		std::cout	<< "\nmain: "	<<	main << "\n"
// 					<< "target " << pend[jacobsthal_number_index[i] * size_of_pair - 1]
// 					<< " idx: " << idx
// 					<< " main[idx]: " << main[idx]<<"\n\n";
// 	}
// 	std::cout << YELLOW"main: "	<<	main	<<	"\n"RESET;
// 	// std::cout << "\n";

// 	pend.clear();

// (void)main;(void)pend;(void)size_of_pair;
// }
