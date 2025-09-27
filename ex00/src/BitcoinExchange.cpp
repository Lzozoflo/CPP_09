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
	while (std::getline(sfile, tmp)) {

		std::cout << "tmp: "<< tmp << std::endl;

		if (tmp.find_first_of(" | ") == std::string::npos || tmp.find_first_of(" | ") != tmp.find_last_of(" | ") - 2 ) {
			std::cout << RED << "Error: bad format in "<< str << " -> '" << ((!tmp.empty()) ? tmp : "") << "'" <<RESET << std::endl;
			continue;
		}
		std::string key = tmp.substr(0, tmp.find_first_of(" | "));
		float value = 0;
		try
		{
			value = this->convert(tmp.substr(tmp.find_last_of(" | "), tmp.length()));
		} catch(const std::string& e){

			std::cout << RED << e << RESET << std::endl;
			continue;
		} catch (const int &v) {

			if (v == 1) {
				std::cout << RED << "Error: bad format in "<< str << " -> '" << ((!tmp.empty()) ? tmp : "") << "'" <<RESET << std::endl;
				continue;
			}
		}


		if (this->pars_date(key)){
			std::cout << RED << "Error: bad input in "<< str <<" -> '" << tmp << "'" << RESET << std::endl;
		}
		(void)value;
		// std::cout << "key : " << key << " value : " << value << std::endl;
		// if (this->pars_date(tmp))

	}

	if (sfile.bad()) {
		throw(std::string("Error: Critical error when reading the file."));
	} else if (!sfile.eof()) {
		throw(std::string("Error: The file wasn't totaly readed."));
	}
	sfile.close();
	(void)str;
}
float	BitcoinExchange::convert(std::string tmp) {
	std::stringstream ss(tmp.c_str());
	float res = 0;
	ss >> res;
	if (!ss.eof() || ss.fail()) {
		throw (1);
	} else if (res > 2147483648) {
		throw (std::string("Error: too large a number."));
	} else if (res < 0){
		throw (std::string("Error: not a positive number."));
	}
	return (res);
}

bool	BitcoinExchange::pars_date(std::string &tmp) {
	(void)tmp;
	// std::stringstream ss(tmp);
	// int years , mounth, day, value;
	// char first_char, second_char, third_char;
	// ss >> years >> first_char >> mounth >> second_char >> day >> third_char >>  >>  >>


	return false;
	return true;
}



void	BitcoinExchange::print_data() {

	for (std::map<std::string, std::string>::iterator it = this->_data_csv.begin(); it != this->_data_csv.end(); it++) {

		std::cout << it->first << "," << it->second <<std::endl;
	}
}
