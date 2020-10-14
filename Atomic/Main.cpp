#include <iostream>
#include "Atomic/Config/Parser.h"
#include "Atomic/API/Wrapper.h"
#include "Atomic/Conversion.h"
#include "Atomic/User.h"

bool rapLowerThan500(const atomic::Item& item) {
    if (item.rap < 1000)
        return true;
    return false;
}

int main()
{
#ifndef VS_DEBUG
    try {
#endif
        
#ifndef VS_DEBUG
    }
    catch (...) {
        // If any errors go unhandled, handle them here
    }
#endif
    return 0;
}