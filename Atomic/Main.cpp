#include <iostream>
#include "Atomic/Config/Parser.h"
#include "Atomic/API/Wrapper.h"
#include "Atomic/Conversion.h"
#include "Atomic/User.h"

int main()
{
#ifndef VS_DEBUG
    try {
#endif
        
#ifndef VS_DEBUG
    }
    catch (...) {
        /*
        All errors are expected to be handled,
        this is just a precaution in case one falls through to prevent the program from closing.
        */
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}