#include <iostream>

int main()
{
#ifndef _DEBUG
    try {
#endif
        // Primary code here
#ifndef _DEBUG
    }
    catch (...) {

    }
#endif
    return 0;
}