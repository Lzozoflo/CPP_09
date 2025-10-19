#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// int	Jacobsthal(int k) {
//     return (round((pow(2, k + 1) + pow(-1, k)) / 3));
// }

std::vector<int> _jacobsthal_number(long n) {

	size_t i = 1;
	long value = 0, last_value = 1;
	std::vector<int> jacobsthal_number_index;
	do
	{
		value = round((pow(2, i + 1) + pow(-1, i)) / 3);
		std::cout <<"value "<< value<< "\n";
		if (value > 1) {
			for (long v = value; v != last_value; v--)
			if (v <= n) {
				jacobsthal_number_index.push_back(v); // (j - 0) for the jacobsthal_number | (j - 2) for index start from 0
			}
			last_value = value;
		}
		i++;
	} while (value < n);

	return (jacobsthal_number_index);
}

int main() {

	std::vector<int> jacobsthal_number_index = _jacobsthal_number(3 + 1);

	std::cout <<"jacobsthal_number_index:";
	for (std::vector<int>::iterator it = jacobsthal_number_index.begin(); it != jacobsthal_number_index.end();it++)
	{
		std::cout  <<" "<< *it;
	}

	std::cout <<"\n";
    return 0;
}
