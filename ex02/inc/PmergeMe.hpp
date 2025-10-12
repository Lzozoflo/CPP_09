
#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN  "\033[32m"
#define BLUE  "\033[34m"
#define YELLOW "\033[33m"

#include <string>
#include <vector>

class PmergeMe {

	private:
	std::vector<int> _vec_stock;
	// std::deque<int> _deq_stock;
	public:
		PmergeMe( void );
		PmergeMe(std::string str);
		PmergeMe &operator=( const PmergeMe &other );
		~PmergeMe( void );

		first_stock(std::string &str);

};



#endif
