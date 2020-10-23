#include <iostream>
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
        try {
            std::vector<atomic::User> r = roblox::getUsersInGroup(650266, 36901726);
            for (auto user = r.begin(); user != r.end(); ++user) {
                std::cout << user->name() << '\n';
            }
        }
        catch (atomic::HttpError error) {
            std::cout << error.message;
        }
#ifndef VS_DEBUG
    }
    catch (...) {
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}