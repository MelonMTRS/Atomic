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

int hmain()
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

int main() {
    rolimons::ItemDB* items;
    try {
        items = new rolimons::ItemDB{ rolimons::getRolimonItems() };
    }
    catch (const std::bad_alloc&) {
        std::cerr << "Rare Allocation Error: Unable to allocate enough memory, doing a stack allocation...\n";
        items = &rolimons::getRolimonItems();
    }
    catch (const atomic::HttpError& error) {
        std::cerr << "FATAL: Failed to get rolimons values, make sure you have an active internet connection then restart Atomic\n";
        std::cin.get();
        std::exit(EXIT_FAILURE);
    }
    if (!config::configExists()) {
        std::cout << "Could not find default config, creating...\n";
        try {
            config::createConfig(config::getDefaultConfig());
        }
        catch (const atomic::HttpError& error) {
            std::cerr << "Error occured while trying to fetch the default config, please restart and try again.\n";
            std::cin.get();
            std::exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}