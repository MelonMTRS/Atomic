#include <iostream>
#include "Atomic/API/Rolimons.h"
#include "Atomic/API/Wrapper.h"
#include "Atomic/Bot.h"
#include "Atomic/Config/Config.h"
#include "Atomic/Config/Parser.h"
#include "Atomic/Config/Parser.h"
#include "Atomic/Conversion.h"
#include "Atomic/Demand.h"
#include "Atomic/Exceptions.h"
#include "Atomic/Exceptions.h"
#include "Atomic/Functions.h"
#include "Atomic/User.h"

int main()
{
#ifndef VS_DEBUG
    try {
#endif
        rolimons::ItemDB items = rolimons::getRolimonItems();
        atomic::AuthUser user = roblox::getUserFromCookie("COOKIE");
        config::Config c = {"testConfig.cfg"};
        std::cout << "Point 1\n";
        atomic::User userToTradeWith = atomic::findUser(user, items);
        std::cout << "Point 2 " << userToTradeWith.name() << '\n';
        atomic::Inventory authInventory = user.getInventory(items);
        std::cout << "Point 3\n";
        atomic::Inventory usersInventory = userToTradeWith.getInventory(items);
        std::cout << "Point 4\n";
        atomic::Offer offer = atomic::makeOffer(authInventory, usersInventory, c);
        std::cout << "Point 5\n";
        for (auto s : offer.getOffering()) {
            std::cout << s.name << '\n';
        }
        std::cout << "-----------------\n";
        for (auto b : offer.getRequesting()) {
            std::cout << b.name << '\n';
        }
        try {
            //roblox::sendTrade(user, atomic::Trade{ NULL, user, userToTradeWith, offer, atomic::TradeType::Outbound });
        }
        catch (atomic::HttpError error) {
            std::cout << "Error: " << error.message;
        }
#ifndef VS_DEBUG
    }
    catch (...) {
        std::cerr << "Unhandled exception occured, ignoring...\n";
    }
#endif
    return EXIT_SUCCESS;
}



// DIVIDER

int release_main() {
    std::cout << "<Loading...>\n";
    rolimons::ItemDB* items;
    atomic::AuthUser user;
    config::Config mainConfig;
    try {
        items = new rolimons::ItemDB{ rolimons::getRolimonItems() };
    }
    catch (const std::bad_alloc&) {
        atomic::throwException("Rare Allocation Error: Unable to allocate enough memory for main.ItemDB, please restart Atomic\n");
    }
    catch (const atomic::HttpError&) {
        atomic::throwException("Failed to get rolimons values, make sure you have an active internet connection\n");
    }
    if (!config::configExists()) {
        atomic::clear();
        std::cout << "Could not find default config, creating...\n";
        try {
            config::createConfig(config::getDefaultConfig());
            std::cout << "Config has been created, please open config.cfg and modify it as desired, then restart Atomic again.";
            std::cin.get();
            std::exit(EXIT_SUCCESS);
        }
        catch (const atomic::HttpError& error) {
            atomic::throwException("Error occured while trying to fetch the default config, please restart and try again.\n");
        }
    }
    mainConfig = {"config.cfg"};
    std::string robloSecurity = mainConfig.getString("ROBLOSECURITY");
    try {
        user = roblox::getUserFromCookie(robloSecurity);
    }
    catch (const atomic::HttpError& error) {
        atomic::throwException("Failed to login, please make sure you added the correct roblosecurity cookie\nStatus code: " + std::to_string(error.status_code) + "\n");
    }
    if (!user.isPremium()) {
        atomic::throwException("Login was a success, however it looks like you don't have premium!\nAtomic cannot trade without it\n");
    }
    return EXIT_SUCCESS;
}