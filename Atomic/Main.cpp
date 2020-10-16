#include <iostream>
#include <thread>
#include <chrono>
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
        rolimons::ItemDB items = rolimons::getRolimonItems();
        atomic::RolimonsItem i = rolimons::getItem(items, 527365852);
        std::cout << i.value;
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