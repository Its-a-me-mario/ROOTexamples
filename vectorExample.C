#include <iostream>
#include <vector>


int vectorExample() {
	std::vector<int> vec;
	//for (int i=0; i<5; i++) vec.push_back(i);

	std::cout << "Vec contains: ";

	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << ' ' << *it;
	}	
	std::cout << std::endl;

	return 0;
}
