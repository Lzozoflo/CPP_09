

#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN  "\033[32m"
#define BLUE  "\033[34m"
#define YELLOW "\033[33m"

#include <ctime>
#include <string>
#include <vector>
#include <deque>

typedef std::vector<int>::const_iterator	vec_const_iterator;
typedef std::deque<int>::const_iterator	deq_const_iterator;

typedef std::vector<int>::iterator	vec_iterator;
typedef std::deque<int>::iterator	deq_iterator;

class PmergeMe {

	private:

		time_t				_start_vec; //sec std::time(NULL)
		std::vector<int>	_vec;
		time_t				_end_vec; //sec std::time(NULL)

		time_t				_start_deq; //sec std::time(NULL)
		std::deque<int>		_deq;
		time_t				_end_deq; //sec std::time(NULL)


		const int			_nb_of_nb;
		const std::string	_Before;


		PmergeMe( void );
		std::string		_stock(int ac, char **av);
		void			_debug_print( void );
		void			_expected_print( void );
		void			_process_vector( void );
		void			_process_deque( void );

	public:
		PmergeMe(int ac, char **av);
		~PmergeMe( void );

};



#endif
