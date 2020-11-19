#include <Windows.h>
#include <iostream>
#include "./Exceptions.h"
#include "./Functions.h"

void atomic::throwException(const std::string& message) {
	MessageBoxA(NULL, message.c_str(), "Atomic Error", MB_ICONERROR);
	std::exit(1);
}