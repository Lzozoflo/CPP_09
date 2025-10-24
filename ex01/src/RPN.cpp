#include "RPN.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

RPN::RPN( void ) {}

static bool issign(char c){
	return (c == '/' || c == '*' || c == '-' || c == '+');
}
RPN::RPN(std::string str) {
	bool space = false;
	for (size_t i = 0; i < str.size(); i++)
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
				int total = 0;
				if (str[i] == '+'){
					total = val1 + val2;
				} else if (str[i] == '-'){
					total = (val1 > val2) ? (val1 - val2) : (val2 - val1);
				} else if (str[i] == '*'){
					total = val1 * val2;
				} else if (str[i] == '/' && val1 != 0 && val2 != 0){
					total = val1 / val2;
				} else {
					throw (std::string("Error"));
				}
				std::cout << val1 << ":"<< val2 << "="<< total << std::endl;
				this->_stock.push(total);
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