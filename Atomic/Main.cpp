#include <iostream>
#include "Atomic/API/Rolimons.h"
#include "Atomic/Config/Parser.h"
#include "Atomic/API/Wrapper.h"
#include "Atomic/Conversion.h"
#include "Atomic/User.h"

int main()
{
#ifndef VS_DEBUG
    try {
#endif
        // Testing rolimons::isProjected
        std::cout << std::boolalpha;
        rolimons::ItemDB items = rolimons::getRolimonItems();
        std::cout << rolimons::isProjected(items, 93068184);
#ifndef VS_DEBUG
    }
    catch (...) {
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}