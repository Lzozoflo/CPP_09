#include "RPN.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

RPN::RPN( void ) {}

static bool issign(char c) {
	return (c == '/' || c == '*' || c == '-' || c == '+');
}


RPN::RPN(std::string str) {
	bool space = false;
	size_t i;
	for (i = 0; i < str.size(); i++)
	{
		if (!space && std::isdigit(str[i])) {

			this->_stock.push(static_cast<int>(str[i]) - 48);
			space = true;

		} else if (!space && issign(str[i])) {

			space = true;
			if (this->_stock.size() < 2) {
				throw (std::string("Error"));
			} else {

				int val1 = this->_stock.top();
				this->_stock.pop();

				int val2 = this->_stock.top();
				this->_stock.pop();

				double total = 0;
				if (str[i] == '+'){
					total = val2 + val1;
				} else if (str[i] == '-'){
					total = val2 - val1;
				} else if (str[i] == '*'){
					total = val2 * val1;
				} else if (str[i] == '/' && val1 != 0){
					total = val2 / val1;
				} else {
					throw (std::string("Error"));
				}
				// std::cout << val1 << " "<< str[i] << " "<< val2 << " = "<< total << std::endl;
				if (total > static_cast<double>(std::numeric_limits<int>::max()) || total < static_cast<double>(std::numeric_limits<int>::min()))
					throw (std::string("Error"));
				this->_stock.push(static_cast<int>(total));
			}
		} else {
			if (space && str[i] == ' ') {
				space = false;
				continue;
			} else {
				throw (std::string("Error"));
			}
		}
	}
	if (i <= 2 || this->_stock.size() > 1)
		throw (std::string("Error"));
	std::cout << this->_stock.top() << std::endl;
}

RPN::RPN( const RPN &other ) {
	*this = other;
}
RPN& RPN::operator=( const RPN &other ){
	if (this != &other) {
		this->_stock = other._stock;
	}
	return (*this);
}
RPN::~RPN( void ) {}