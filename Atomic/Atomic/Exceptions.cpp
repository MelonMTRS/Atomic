#include <iostream>
#include "./Functions.h"
#include "./Exceptions.h"

void atomic::throwException(const std::string& message) {
	atomic::clear();
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cerr << message;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cin.get();
	std::exit(EXIT_FAILURE);
}