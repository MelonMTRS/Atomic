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
        rolimons::ItemDB items = rolimons::getRolimonItems();
        atomic::User r = { 1480997 };
        atomic::Inventory userInv = r.getInventory(items);
        //userInv.randomizeInventory();
        std::cout << userInv[0].name;
#ifndef VS_DEBUG
    }
    catch (...) {
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}