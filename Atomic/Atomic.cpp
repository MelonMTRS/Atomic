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
        atomic::AuthUser user = roblox::getUserFromCookie("_|WARNING:-DO-NOT-SHARE-THIS.--Sharing-this-will-allow-someone-to-log-in-as-you-and-to-steal-your-ROBUX-and-items.|_86E9284958832FBE80B0040C155A8713042EDF33F52BDD6CAF810F5507D38096B87BBDB587971DE1E05FA1CA8432DE9EDE255BC729F099D712CFC5C3D3D579FD7A48ACC63D74F1746790C7196F5939CBBA480389EC790771F2D3BADC3439866D7E9ED3AA7922FF2BA0C269C96B3158CA4D47468818F340704181D741D411D262256018ACC4E30AC3B28BBD7ACC3C584BADC154945905878D368C736D61A4C584F28E0A1D73B96E2490022EC741E4ABB7403563506553AAF6BF9A22CC3763CAFEAB4F249C111F577CAF5883F1C356B857FCD05BAE5D571E181F569067348FF53EF1FA449E509EBF63124D4432A036AA62E654AD9652FF46E6BAB3E0B5AACA0A751145F61996D51AB2F6D0FBFA9CB61D28C60E95B5E1BD57A905F83F78AB1D7DD7F1841756");
        config::Config c = {"testConfig.cfg"};
        std::cout << "Point 1\n";
        atomic::User userToTradeWith = atomic::findUser(user, items);
        std::cout << "Point 2 " << userToTradeWith.name() << '\n';
        atomic::Inventory authInventory = user.getInventory(items);
        std::cout << "Point 3\n";
        atomic::Inventory usersInventory = userToTradeWith.getInventory(items);
        std::cout << "Point 4\n";
        auto [offer, profit] = atomic::makeOffer(authInventory, usersInventory, c);
        std::cout << "Point 5\n";
        for (auto s : offer.getOffering()) {
            std::cout << s.name << " (" << s.userAssetId << ")" << '\n';
        }
        std::cout << "-----------------\n";
        for (auto b : offer.getRequesting()) {
            std::cout << b.name << " (" << b.userAssetId << ")" << '\n';
        }
        std::cout << "Total profit: " << profit << '\n';
        std::cin.get();
        try {
            roblox::sendTrade(user, atomic::Trade{ NULL, user, userToTradeWith, offer, atomic::TradeType::Outbound });
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