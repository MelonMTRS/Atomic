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

std::string operating_system = "";

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

void clear() {
    std::system("cls");
}

void throwException(std::string message) {
    clear();
    std::cerr << message;
    std::cin.get();
    std::exit(EXIT_FAILURE);
}

int main() {
    std::cout << "<Loading...>\n";
    rolimons::ItemDB* items;
    atomic::AuthUser user;
    config::Parser mainConfig;
    mainConfig = config::parse("config.cfg");
    try {
        items = new rolimons::ItemDB{ rolimons::getRolimonItems() };
    }
    catch (const std::bad_alloc&) {
        clear();
        std::cerr << "Rare Allocation Error: Unable to allocate enough memory, doing a stack allocation...\n";
        items = &rolimons::getRolimonItems();
    }
    catch (const atomic::HttpError& error) {
        throwException("FATAL: Failed to get rolimons values, make sure you have an active internet connection then restart Atomic\n");
    }
    if (!config::configExists()) {
        std::cout << "Could not find default config, creating...\n";
        try {
            config::createConfig(config::getDefaultConfig());
            std::cout << "Config has been created, please open config.cfg and modify it as desired, then run Atomic again.";
            std::cin.get();
            std::exit(EXIT_SUCCESS);
        }
        catch (const atomic::HttpError& error) {
            throwException("Error occured while trying to fetch the default config, please restart and try again.\n");
        }
    }
    std::string robloSecurity = std::get<std::string>(config::get(mainConfig, "ROBLOSECURITY"));
    try {
        user = roblox::getUserFromCookie(robloSecurity);
    }
    catch (const atomic::HttpError& error) {
        throwException("Failed to login, please make sure you added the correct roblosecurity cookie\nStatus code: " + std::to_string(error.status_code) + "\n");
    }
    if (!user.isPremium()) {
        throwException("Login was a success, however it looks like you don't have premium!\nAtomic cannot trade without it\n");
    }
    return EXIT_SUCCESS;
}