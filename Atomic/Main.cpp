#include <iostream>
#include "Atomic/Config/Config.h"
#include "Atomic/Demand/Demand.h"
#include "Atomic/Exceptions.h"
#include "Atomic/Config/Parser.h"
#include "Atomic/API/Rolimons.h"
#include "Atomic/API/Wrapper.h"
#include "Atomic/Config/Parser.h"
#include "Atomic/Conversion.h"
#include "Atomic/User.h"
#include "Atomic/Functions.h"
#include "Atomic/Bot.h"

int main()
{
#ifndef VS_DEBUG
    try {
#endif
        
#ifndef VS_DEBUG
    }
    catch (...) {
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}

int release_main() {
    rolimons::ItemDB* items;
    try {
        items = new rolimons::ItemDB{ rolimons::getRolimonItems() };
    }
    catch (const std::bad_alloc&) {
        std::cout << "Rare Allocation Error: Unable to allocate enough memory, please re-start.\n";
        std::cin.get();
        std::exit(EXIT_FAILURE);
    }
    if (!config::configExists()) {
        std::cout << "Could not find default config, creating...\n";
    }
    return EXIT_SUCCESS;
}