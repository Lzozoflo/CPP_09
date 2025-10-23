

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#define BLACK	"\033[30m"
#define RESET	"\033[0m"
#define RED		"\033[31m"
#define GREEN 	"\033[32m"
#define BLUE 	"\033[34m"
#define YELLOW	"\033[33m"
#define PURPLE	"\033[35m"
#define CYAN	"\033[36m"

#include <ctime>
#include <string>
#include <vector>
#include <deque>

typedef std::vector<size_t>::const_iterator	vec_const_iterator;
typedef std::deque<size_t>::const_iterator	deq_const_iterator;

typedef std::vector<size_t>::iterator	vec_iterator;
typedef std::deque<size_t>::iterator	deq_iterator;

class PmergeMe {

	private:

		clock_t					_start_vec; //sec std::time(NULL)
		std::vector<size_t>		_vec;
		clock_t					_end_vec; //sec std::time(NULL)

		clock_t					_start_deq; //sec std::time(NULL)
		std::deque<size_t>		_deq;
		clock_t					_end_deq; //sec std::time(NULL)


		const int				_nb_of_nb;
		const std::string		_Before;


		PmergeMe( void );
		std::string				_stock(int ac, char **av);
		void					_expected_print( void );
		void					_process_vector( void );
		void					_process_deque( void );

	public:
		PmergeMe(int ac, char **av);
		~PmergeMe( void );

};



#endif
