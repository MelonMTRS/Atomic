#include <iostream>
#include "Atomic/API/Wrapper.h"

int main()
{
#ifndef VS_DEBUG
    try {
#endif
        // Primary code here
#ifndef VS_DEBUG
    }
    catch (...) {
        // If any errors go unhandled, handle them here
    }
#endif
    return 0;
}