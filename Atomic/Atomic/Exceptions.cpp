#include <iostream>
#include <Windows.h>
#include "./Functions.h"
#include "./Exceptions.h"

void atomic::throwException(const std::string& message) {
	MessageBoxA(NULL, message.c_str(), "Atomic Error", MB_ICONERROR);
	std::exit(1);
}