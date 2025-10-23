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
		// std::cout <<"value "<< value<< "\n";
		if (value > 1) {
			for (long v = value; v != last_value; v--)
			if (v <= n) {
				jacobsthal_number_index.push_back((v)); // (j - 0) for the jacobsthal_number | (j - 2) for index start from 0
			}
			last_value = value;
		}
		i++;
	} while (value < n);

	return (jacobsthal_number_index);
}

// std::vector<int> _jacobsthal_number_size_of_pair(long n, long size_of_pair) {
// 	std::vector<int> jacobsthal_number_index = _jacobsthal_number(5 + 1);

// 	std::cout <<"jacobsthal_number_index:";
// 	size_t i = 0;
// 	for (std::vector<int>::iterator it = jacobsthal_number_index.begin(); it != jacobsthal_number_index.end();it++) {
// 		std::cout  <<" "<< ((*it * size_of_pair) - 1 );

// 	}
// 	std::cout <<"\n";





// }


int main() {


	std::vector<int> jacobsthal_number_size_of_pair = _jacobsthal_number(1 + 1);

	std::cout <<"jacobsthal_number_size_of_pair:";
	for (std::vector<int>::iterator it = jacobsthal_number_size_of_pair.begin(); it != jacobsthal_number_size_of_pair.end();it++)
	{
		std::cout  <<" "<< *it;
	}



	std::cout <<"\n";
    return 0;
}
















#include <iostream>
#include <vector>
using namespace std;

// int upperBound(vector<int> &arr, int target) {
// 	int lo = 0, hi = arr.size() - 1;
//     int res = arr.size();
//   	while(lo <= hi) {
//       	int mid = (lo + (hi - lo)/2);

//         // If arr[mid] > target, then arr[mid] can be
//         // the upper bound so store mid in result and
//         // search in left half, i.e. arr[lo...mid-1]
//       	if(arr[mid] > target) {
//           	res = mid;
//             hi = (mid) - 1;
//         }

//         // If arr[mid] <= target, then upper bound
//         // cannot lie in the range [lo...mid], so
//         // search in right half, i.e. arr[mid+1...hi]
//       	else
//             lo = mid + 1;
//     }
//   	return res;
// }

// int upperBound(vector<int> &arr, int target, size_t size_of_pair) {
// 	int lo = 0, hi = arr.size() - 1;
//     int res = arr.size();
//   	while(lo <= hi) {
//       	int mid = (lo + (hi - lo)/2) * size_of_pair;

//         // If arr[mid] > target, then arr[mid] can be
//         // the upper bound so store mid in result and
//         // search in left half, i.e. arr[lo...mid-1]
//       	if(arr[mid * size_of_pair] > target) {
//           	res = mid * size_of_pair;
//             hi = (mid * size_of_pair) - 1;
//         }

//         // If arr[mid] <= target, then upper bound
//         // cannot lie in the range [lo...mid], so
//         // search in right half, i.e. arr[mid+1...hi]
//       	else
//             lo = mid + 1;
//     }
//   	return res;
// }

// int upperBoundBlock(std::vector<int> &arr, int target, int blockSize) {
// 	int n = arr.size() / blockSize; // nombre de blocs
// 	int li = 0, hi = n - 1;
// 	int res = n;

// 	while (li <= hi) {
// 		int mid = li + (hi - li) / 2;
// 		int val = arr[mid * blockSize + (blockSize - 1)]; // dernier du bloc
// 		std::cout << "arr: " << val<< "\n";

// 		if (val > target) {
// 			res = mid;
// 			hi = mid - 1;
// 		} else {
// 			li = mid + 1;
// 		}
// 	}

// 	return res * blockSize; // index du bloc
// }
// int main() {

//     vector<int> arr = {2, 3, 4, 5, 5, 5, 5, 6, 7, 7, 10, 11, 11, 25};
// 	int blockSize = 2;
//     int target = 5;

//     cout << upperBoundBlock(arr, target, blockSize);
//     return 0;
// }
