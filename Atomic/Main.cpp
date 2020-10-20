#include <iostream>
#include "Atomic/Config/Parser.h"
#include "Atomic/API/Rolimons.h"
#include "Atomic/API/Wrapper.h"
#include "Atomic/Config/Parser.h"
#include "Atomic/Conversion.h"
#include "Atomic/User.h"
#include "Atomic/Functions.h"

int main()
{
#ifndef VS_DEBUG
    try {
#endif
        config::Parser p = config::parse("config.cfg");
        config::ParseValue val = config::get(p, "test");
        config::ParseValue another_value = config::get(p, "another_value");
        std::cout << "test: " << std::get<std::string>(val) << '\n';
        std::cout << "another_value: " << std::get<int>(another_value) << '\n';
#ifndef VS_DEBUG
    }
    catch (...) {
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}