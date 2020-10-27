#include <iostream>
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
        rolimons::ItemDB items = rolimons::getRolimonItems();
        rolimons::RolimonsUser user = rolimons::getUser(items, 1480997);
        std::cout << "Total Rap: " << user.rap << "\nTotal Value: " << user.value;
#ifndef VS_DEBUG
    }
    catch (...) {
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}