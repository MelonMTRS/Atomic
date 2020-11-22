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
        atomic::AuthUser user = roblox::getUserFromCookie("_|WARNING:-DO-NOT-SHARE-THIS.--Sharing-this-will-allow-someone-to-log-in-as-you-and-to-steal-your-ROBUX-and-items.|_6D64AB2352A1C5987813DC5AC6331E93F22450D2A7A4466347A89D3C7BEC1B4A2006BD9626830594450B7D526407657F8CAB863A152198F6A2D8DA127D70DF8EFE16EC712DFD1CDDE30C1FEC1375CA66DAFA83C7773B8077A853D897EADAD85FF52A4E87C2157458BE404A1A4189FCC3BCE2A8A977D4DE9BEF76EA9240EAAD07E0F19C75A8E782D5451EA0B8C37086BD0BBB461B9996D2912C9EF6C59733FA2DBE594DE89F0F341BB4D773B331B78FCA9AFA6CB0EB8ABC4CBAF07BA339C192CB1B077A28011D3BAEEE89B70635C3E9A91FE30149A8B9D6A2B3E1A82984AC778E8C6653E0DFF9CA60457BCA372A30530CE4770E369BB43611A1432FD971679D68BBEDD77663A430BF3BBD8D6FA16A47519F1155D3C245FC67E49EF93E249F50630437E99C");
        config::Config c = {"testConfig.cfg"};
        std::cout << "Point 1\n";
        atomic::User userToTradeWith = atomic::findUser(user, items);
        std::cout << "Point 2\n";
        atomic::Inventory authInventory = user.getInventory(items);
        std::cout << "Point 3\n";
        atomic::Inventory usersInventory = userToTradeWith.getInventory(items);
        std::cout << "Point 4\n";
        atomic::Offer offer = atomic::makeOffer(authInventory, usersInventory, c);
        std::cout << "Point 5\n";
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