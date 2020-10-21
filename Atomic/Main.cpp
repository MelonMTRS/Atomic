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
        std::cout << std::boolalpha;
        rolimons::ItemDB items = rolimons::getRolimonItems();
        while (true) {
            std::cout << rolimons::getRandomItem(items).name << '\n';
        }
#ifndef VS_DEBUG
    }
    catch (...) {
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}