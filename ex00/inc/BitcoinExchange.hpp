
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN  "\033[32m"
#define BLUE  "\033[34m"
#define YELLOW "\033[33m"

#include <string>
#include <map>

class BitcoinExchange {

	private:
		std::map<std::string, std::string> _data_csv;
		void	print_data();
		bool	pars_date(std::string &tmp);
		float	convert(std::string tmp);
		void	total_at_date(std::string key, float value);

	public:
		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange &other );
		BitcoinExchange &operator=( const BitcoinExchange &other );
		~BitcoinExchange( void );
		void	output( std::string str );
};



#endif
