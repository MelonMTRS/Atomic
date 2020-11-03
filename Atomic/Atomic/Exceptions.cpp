#include <iostream>
#include "./Functions.h"
#include "./Exceptions.h"

void atomic::throwException(const std::string& message) {
	atomic::clear();
	std::cerr << message;
	std::cin.get();
	std::exit(EXIT_FAILURE);
}