#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>




BitcoinExchange::BitcoinExchange(){

	// 1. Open the config_file to read.
	std::ifstream sfile("data.csv");

	// 2. Check if is open.
	if (!sfile.is_open()) {
		throw (std::string("Erreur : data.csv can't be open."));
	}
	// 3. Read all the config_file.
	std::string tmp;
	std::getline(sfile, tmp);
	if (tmp.compare("date,exchange_rate")){
		throw (std::string("bad format in data.csv. -> " + tmp + "\nexpected: 'date,exchange_rate'"));
	}
	while (std::getline(sfile, tmp)) {

		if (tmp.find_first_of(',') == std::string::npos && tmp.find_first_of(',') != tmp.find_last_of(',')) {
			throw (std::string("bad format in data.csv. -> " + tmp));
		}
		std::string key = tmp.substr(0, tmp.find_first_of(','));
		std::string value = tmp.substr(11, tmp.length());
		if (this->_data_csv.find(key) != this->_data_csv.end()) {

			throw (std::string("same date in data.csv. -> " + tmp));
		}
		this->_data_csv[key] = value;
	}

	// Debug Print all the content stocked
	// this->print_data();

	//5. Check if we read all the file or not.
	if (sfile.bad()) {
		throw(std::string("Error: Critical error when reading the file."));
	} else if (!sfile.eof()) {
		throw(std::string("Error: The file wasn't totaly readed."));
	}
	sfile.close();
}

void	BitcoinExchange::output( std::string str ) {

	// 1. Open the config_file to read.
	std::ifstream sfile(str.c_str());

	// 2. Check if is open.
	if (!sfile.is_open()) {
		throw (std::string("Erreur : "+ str +" can't be open."));
	}

	// 3. Read all the config_file.
	std::string tmp;
	std::getline(sfile, tmp);
	if (tmp.compare("date | value")){
		throw (std::string("bad format in data.csv. -> " + tmp + "\nexpected: 'date | value'"));
	}
	while (std::getline(sfile, tmp)) {

		// std::cout << "tmp: "<< tmp << std::endl;

		if (tmp.find_first_of(" | ") == std::string::npos || tmp.find_first_of(" | ") != tmp.find_last_of(" | ") - 2 ) {
			std::cout << RED << "Error: bad format => '" << ((!tmp.empty()) ? tmp : "") << "'" <<RESET << std::endl;
			continue;
		}
		std::string key = tmp.substr(0, tmp.find_first_of(" | "));
		float value = 0;
		try
		{
			value = this->convert(tmp.substr(tmp.find_last_of(" | ") + 1, tmp.length()));
		} catch(const std::string& e){
			std::cout << RED << e << RESET << std::endl;
			continue;
		} catch (const int &v) {
			if (v == 1) {
				std::cout << RED << "Error: bad format => " << tmp << RESET << std::endl;
				continue;
			}
		}

		if (!this->pars_date(key)){
			std::cout << RED << "Error: bad input => " << key << RESET << std::endl;
			continue;
		}

		this->total_at_date(key, value);
		// std::cout << key << " => " << value << " = not now" << std::endl;
	}


	if (sfile.bad()) {
		throw(std::string("Error: Critical error when reading the file."));
	} else if (!sfile.eof()) {
		throw(std::string("Error: The file wasn't totaly readed."));
	}
	sfile.close();
	(void)str;
}


void	BitcoinExchange::total_at_date(std::string key, float value) {
	(void)key;(void)value;

	std::map<std::string, std::string>::iterator it = this->_data_csv.lower_bound(key);
	std::string str;
	if (it != this->_data_csv.end()) {
		// std::cout << "Clé: " << it->first << ", Valeur: " << it->second << std::endl;
		str = it->second;
	}
	else {
		std::map<std::string, std::string>::iterator iter = this->_data_csv.end();
		iter--;
		str = iter->second;
		// std::cout << "Clé: " << iter->first << ", Valeur: " << iter->second << std::endl;
	}
	std::stringstream ss(str);
	float res = 0;
	ss >> res;
	float total = res * value;
	std::cout << key << " => " << value << " = " << total << std::endl;

}

float	BitcoinExchange::convert(std::string tmp) {
	// std::cout << tmp << std::endl;
	std::stringstream ss(tmp.c_str());
	float res = 0;
	ss >> res;
	if (!ss.eof() || ss.fail()) {
		throw (1);
	} else if (res > static_cast<float>(1000)) {
		throw (std::string("Error: too large a number."));
	} else if (res < 0){
		throw (std::string("Error: not a positive number."));
	}
	return (res);
}

bool	is_31day(int mounth){
	return (mounth == 1 || mounth == 3 || mounth == 5 || mounth == 7 || mounth == 8 || mounth == 10 || mounth == 12);
}

bool	BitcoinExchange::pars_date(std::string &tmp) {
	std::stringstream ss(tmp);
	int years , mounth, day;
	char first_char, second_char;
	ss >> years >> first_char >> mounth >> second_char >> day;

	if (!ss.eof() || ss.fail() || first_char != '-' || second_char != '-' || !(day > 0 && day < 32) || !(mounth > 0 && mounth < 13)) {
		return false;
	}
	if (is_31day(mounth)){
		return true;
	} else if (!is_31day(mounth) && mounth != 2 && day == 31) {
		return false;
	} else if (mounth == 2) {
		if (((years % 4 == 0 && years % 100 != 0) || years % 400 == 0) && day > 29) {
			return false;
		} else if (!((years % 4 == 0 && years % 100 != 0) || years % 400 == 0) && day > 28){
			return false;
		}
		return true;
	} else {
		std::cout<< RED << "false if i dont have thit one" << RESET << std::endl;
		return false;
	}
}

void	BitcoinExchange::print_data() {

	for (std::map<std::string, std::string>::iterator it = this->_data_csv.begin(); it != this->_data_csv.end(); it++) {

		std::cout << it->first << "," << it->second <<std::endl;
	}
}












BitcoinExchange::BitcoinExchange( const BitcoinExchange &other ) {
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange &other ) {
	if (this != &other){
		this->_data_csv = other._data_csv;
	}
}

BitcoinExchange::~BitcoinExchange( void ) { }