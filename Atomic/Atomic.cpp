#include <filesystem>
#include <iostream>
#include <thread>
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

namespace fs = std::filesystem;

constexpr bool isDebug = false;

int debug()
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




int release() {
    std::cout << "<Loading...>\n";
    // TODO: Test internet connection
    bool atomicActive = true;
    rolimons::ItemDB items = rolimons::getRolimonItems();
    atomic::AuthUser user;
    config::Config mainConfig;
    if (!fs::is_directory(fs::current_path() / "data")) {
        fs::create_directory(fs::current_path() / "data");
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
    try {
        user = roblox::getUserFromCookie(mainConfig.getString("ROBLOSECURITY"));
    }
    catch (const atomic::ForbiddenError& error) {
        atomic::throwException("Failed to login, please make sure you added the correct ROBLOSECURITY cookie and that you have an active internet connection\n");
    }
    if (!user.isPremium()) {
        atomic::throwException("Login was a success, however it looks like you don't have premium!\nAtomic cannot trade without it\n");
    }
    atomic::clear();
    std::cout << "Login to " << user.name() << " successful!\n";
    std::cout << "Fetching demand info for user's inventory...\n";
    std::map<int64_t, atomic::Demand> itemsSet = {};
    for (auto& item : user.getInventory(items)) {
        try {
            if (item.demand == atomic::Demand::NotAssigned && itemsSet.find(item.id) == itemsSet.end()) {
                atomic::Demand itemDemand = atomic::getItemDemand(item);
                std::cout << "Set demand of " << item.name << " to " << atomic::getDemandString(itemDemand) << '\n';
                rolimons::setItemDemand(items, item.id, itemDemand);
                itemsSet[item.id] = itemDemand;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        catch (const atomic::HttpError&) {
            std::cout << "Error occured while fetching demand for " << item.name << '\n';
        }
    }
    if (auto inventory = user.getInventory(items); inventory.item_count() < 2) {
        std::cout << "Warning: You only have (" << inventory.item_count() << ") limited(s) in your inventory, Atomic may have problems finding good trades\n";
    }
    if (mainConfig.getBool("check_inbound_trades")) {
        // TODO: Inbound
    }
    std::thread update_values([&]() {
        while (atomicActive) {
            std::this_thread::sleep_for(std::chrono::minutes(mainConfig.getInt64("update_values")));
            items = rolimons::getRolimonItems();
        }
    });
    std::int64_t rolls = 0;
    while (atomicActive) {
        rolls++;
        if (rolls % 25 == 0)
            atomic::clear(); // don't wanna get the memory to 95% now
        std::cout << "Looking for a user to trade with...\n";
        atomic::User trader = atomic::findUser(user, items);
        std::cout << "Creating a trade with " << trader.name() << " (" << trader.getId() << ")...\n";
        try {
            auto [offer, gain] = atomic::makeOffer(user.getInventory(items), trader.getInventory(items), mainConfig, items);
            roblox::sendTrade(user, atomic::Trade{ NULL, user, trader, offer, atomic::TradeType::Outbound });
            std::cout << "Trade created with a value gain of " << gain << "\n";
        }
        catch (const atomic::TradeFormFailure& tradeFailure) {
            std::cerr << "Failed to create a trade with " << trader.name() << '\n';
        }
        catch (const atomic::HttpError& httpError) {
            std::cerr << "Error occured while trying to send the trade, trade ratio may be too restricting...\n";
        }
        std::cout << "Waiting " << mainConfig.getString("time_between_trade") << " seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(mainConfig.getInt64("time_between_trade")));
    }
    return EXIT_SUCCESS;
}

int main() {
    if (isDebug)
        debug();
    else
        release();
}