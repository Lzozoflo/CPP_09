
#ifndef RPN_HPP
#define RPN_HPP

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN  "\033[32m"
#define BLUE  "\033[34m"
#define YELLOW "\033[33m"

#include <string>
#include <stack>

class RPN {

	private:
		RPN( void );
		RPN( const RPN &other );
		RPN& operator=( const RPN &other );
		std::stack<int> _stock;
	public:
		RPN(std::string str);
		~RPN( void );
};



#endif
