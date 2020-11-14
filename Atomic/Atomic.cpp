#include <iostream>
#include "Atomic/Config/Config.h"
#include "Atomic/Demand.h"
#include "Atomic/Exceptions.h"
#include "Atomic/Config/Parser.h"
#include "Atomic/API/Rolimons.h"
#include "Atomic/API/Wrapper.h"
#include "Atomic/Config/Parser.h"
#include "Atomic/Conversion.h"
#include "Atomic/User.h"
#include "Atomic/Exceptions.h"
#include "Atomic/Functions.h"
#include "Atomic/Bot.h"

int main()
{
#ifndef VS_DEBUG
    try {
#endif
        rolimons::ItemDB items = rolimons::getRolimonItems();
        atomic::AuthUser user = roblox::getUserFromCookie("_|WARNING:-DO-NOT-SHARE-THIS.--Sharing-this-will-allow-someone-to-log-in-as-you-and-to-steal-your-ROBUX-and-items.|_E8AF547002B0310E8395FD367576A2D219D96BB2FD5E77C3107C8EB74ECDE00766AF7D394BABB0A476A8CC3851ECA554B3A0E7A1F227B7AEF9CA6EDA09C250F2261EFBC28D915B4B8C517003983CC4537657AF5D5BB1CC68E80054D5FB357033CA53D399BDA5F138AE55F240784A6650FE0A632EB250B3F418CF761D578C0B6B4F8FAE89DFE3133AA3FB3D3BA17E0DA962808031D09EEC3B15AA96AF123D25029B79E48E12529977FFB91B8F0095AFAA856EFCEF244A11EBB4FDEF7247EB96BEB37922477288279B205206644378F9EDE1D9BB8534D4A3958723260295C4F04D676E6D2756C0AE4AFE024C1A0EF5BE6766908F567C0627BA644879F48BF865C2BD04E6AD1E0048AAA01B0CE3E43DED9188E93000F6E48C869E1535D6B49CEF0E545D0AA4");
        atomic::Trade trade = roblox::getTrade(user, items, 228001213);
        atomic::TradeAction action = atomic::evaluateTrade(items, trade);
        if (action == atomic::TradeAction::Accept) {
            std::cout << "Accept it\n";
}
        else if (action == atomic::TradeAction::Ignore) {
            std::cout << "Ignore it\n";
        }
        else if (action == atomic::TradeAction::Decline) {
            std::cout << "Decline it\n";
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
        atomic::clear();
        std::cerr << "Rare Allocation Error: Unable to allocate enough memory, doing a stack allocation...\n";
        items = &rolimons::getRolimonItems();
    }
    catch (const atomic::HttpError& error) {
        atomic::throwException("FATAL: Failed to get rolimons values, make sure you have an active internet connection then restart Atomic\n");
    }
    if (!config::configExists()) {
        atomic::clear();
        std::cout << "Could not find default config, creating...\n";
        try {
            config::createConfig(config::getDefaultConfig());
            std::cout << "Config has been created, please open config.cfg and modify it as desired, then run Atomic again.";
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