#pragma once
#include <iostream>
#include <boost/filesystem.hpp>

int main() {
	printf("boost");
	boost::filesystem::path p{"."};
	std::cout << "Current path: " << p << std::endl;
	getchar();


	return 0;
}
