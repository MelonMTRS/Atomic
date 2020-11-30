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
        atomic::AuthUser user = roblox::getUserFromCookie("_|WARNING:-DO-NOT-SHARE-THIS.--Sharing-this-will-allow-someone-to-log-in-as-you-and-to-steal-your-ROBUX-and-items.|_AE357615435BF4EE56EC5945BDA6611AAC728FCBBE5808A2934EEEBF3723C64986A46BC7DB5AE90CC6825D37D495E53DFE13D239BEC6FA5FC4DDB0DE8D3D3A39DC44506D98776F23A6D70AAEB325516D5E6D81479CB8B771BD069A8E2472783C3F1D9ED26ECB200ECE4EE80DE19B1C2D97EF888E37BDE37ED025611D11D6B8A5DB0406507F110C5EA753DC10A6242147C85A91C3E6255F0A77EEFF634088AA63B03707F53C32B90BAF80C91BF1E56CDD920DB7F4A23BBF7B68BB7936D08B6A1CCFF4B9905937D4AC7715CA5188278954067922E2A62B33DD823C07F21D47FFB7A485D680C73D1FCA4EEF5FE9BEAA398502758AD59C1D327402887E73CFC11060340DCD34212F8140A7288FD5D5E2AE8E7EE4B8E2F601E91595EC8609850B6A206DA76185");
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