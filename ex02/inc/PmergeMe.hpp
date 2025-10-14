
#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN  "\033[32m"
#define BLUE  "\033[34m"
#define YELLOW "\033[33m"

#include <string>
#include <vector>
#include <deque>

typedef std::vector<int>::iterator	vec_iterator;
typedef std::deque<int>::iterator	deq_iterator;

class PmergeMe {

	private:

		const int			_nb_of_nb;

		// time_t				_start_vec; //sec std::time(NULL) + TIMEOUT
		std::vector<int>	_vec;
		// time_t				_start_deq; //sec std::time(NULL) + TIMEOUT
		std::deque<int>	_deq;


		PmergeMe( void );
		void	_stock(int ac, char **av);
		void	_debug_print(void);
		void	_expected_print();

	public:
		PmergeMe(int ac, char **av);
		~PmergeMe( void );

};



#endif
