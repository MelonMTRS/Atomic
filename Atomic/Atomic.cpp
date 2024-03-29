#include <filesystem>
#include <iostream>
#include <fstream>
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
// json
#include "Atomic/rapidjson/writer.h"
#include "Atomic/rapidjson/stringbuffer.h"

namespace fs = std::filesystem;
using namespace std::chrono_literals;

constexpr bool isDebug = false;

int debug()
{
    
    return EXIT_SUCCESS;
}

int release() {
#ifndef VS_DEBUG
    try {
#endif
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
            std::cout << "Could not find default config, creating...\n";
            try {
                config::createConfig(config::getDefaultConfig());
                std::cout << "Config has been created, please open config.cfg and modify it as desired, then restart Atomic again.";
                std::cin.get();
                std::exit(EXIT_SUCCESS);
            }
            catch (const atomic::HttpError& error) {
                atomic::throwException(error.message + " please restart and try again.\n");
            }
        }
        mainConfig = { "config.cfg" };
        auto [success, message] = config::validateConfig(mainConfig);
        if (!success)
            atomic::throwException(message);
        auto clear = [&]() {
            if (atomic::lower(mainConfig.getString("operating_system")) == "windows")
                std::system("cls");
            else
                std::system("clear");
        };
        try {
            user = roblox::getUserFromCookie(mainConfig.getString("ROBLOSECURITY"));
        }
        catch (const atomic::ForbiddenError& error) {
            atomic::throwException("Failed to login, please make sure you added the correct ROBLOSECURITY cookie and that you have an active internet connection\n");
        }
        if (!user.isPremium()) {
            atomic::throwException("Login was a success, however it looks like you don't have roblox premium!\nAtomic cannot trade without it\n");
        }
        clear();
        std::cout << "Login to " << user.name() << " successful!\n";
        if (atomic::lower(mainConfig.getString("trade_by")) == "rap") {
            std::cout << "WARNING: trade_by config setting is set to rap, this is generally unrecommended, consider changing it to value\n";
            std::this_thread::sleep_for(3s);
        }
        std::cout << "Fetching demand info for user's inventory...\n";
        std::int64_t lastUpdatedDemand = 0;
        rapidjson::Document demandData;
        if (fs::is_regular_file(fs::current_path() / "data\\playerdemand.json")) {
            std::string demandContent = atomic::readFile("data\\playerdemand.json");
            demandData.Parse(demandContent.c_str());
            if (demandData["lastUpdated"].IsInt64()) {
                lastUpdatedDemand = demandData["lastUpdated"].GetInt64();
            }
        }
        if (lastUpdatedDemand == 0 || (atomic::getUnixTime() - lastUpdatedDemand) > 259200) {
            std::map<int64_t, atomic::Demand> itemsSet = {};
            for (auto& item : user.getInventory(items)) {
                try {
                    if (item.demand == atomic::Demand::NotAssigned && itemsSet.find(item.id) == itemsSet.end()) {
                        atomic::Demand itemDemand = atomic::getItemDemand(item);
                        std::cout << "Set demand of " << item.name << " to " << atomic::getDemandString(itemDemand) << '\n';
                        rolimons::setItemDemand(items, item.id, itemDemand);
                        itemsSet[item.id] = itemDemand;
                        std::this_thread::sleep_for(500ms);
                    }
                }
                catch (const atomic::HttpError&) {
                    std::cout << "Error occured while fetching demand for " << item.name << '\n';
                }
            }
            rapidjson::Document playerDemandData;
            playerDemandData.Parse("{\"lastUpdated\": 0,\"items\": {}}");
            playerDemandData["lastUpdated"] = atomic::getUnixTime();
            for (const auto& [id, demand] : itemsSet) {
                rapidjson::Value idString = { std::to_string(id).c_str(), playerDemandData.GetAllocator() };
                rapidjson::Value demandString = { atomic::getDemandString(demand).c_str(), playerDemandData.GetAllocator() };
                playerDemandData["items"].AddMember(idString, demandString, playerDemandData.GetAllocator());
            }
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            playerDemandData.Accept(writer);
            atomic::writeFile("data\\playerdemand.json", buffer.GetString());
        }
        else {
            std::cout << "Found cached demand information (" << atomic::secondsToTime(atomic::getUnixTime() - lastUpdatedDemand) << " old)\n";
            for (auto asset = demandData["items"].MemberBegin(); asset != demandData["items"].MemberEnd(); ++asset) {
                atomic::Demand itemDemand = atomic::getDemandFromString(asset->value.GetString());
                rolimons::setItemDemand(items, std::stoull(asset->name.GetString()), itemDemand);
            }
        }
        if (auto inventory = user.getInventory(items); inventory.item_count() < 2) {
            std::cout << "Warning: You only have (" << inventory.item_count() << ") limited(s) in your inventory, Atomic may have problems finding good trades\n";
        }
        if (mainConfig.getBool("check_inbound_trades")) {
            // Inbound trades are handled silently
            std::thread inboundTrades([&]() {
                while (atomicActive) {
                    std::vector<int64_t> trades;
                    try {
                        std::vector<int64_t> trades = roblox::getTrades(user, atomic::TradeType::Inbound);
                    }
                    catch (const atomic::HttpError& error) {
                        continue;
                    }
                    for (int64_t& tradeId : trades) {
                        try {
                            atomic::Trade trade = roblox::getTrade(user, items, tradeId);
                            atomic::TradeAction action = atomic::evaluateTrade(items, trade, mainConfig);
                            if (action == atomic::TradeAction::Accept)
                                roblox::acceptTrade(user, tradeId);
                            else if (action == atomic::TradeAction::Decline)
                                roblox::declineTrade(user, tradeId);
                        }
                        catch (...) {}
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(mainConfig.getInt64("time_between_check")));
                }
                });
        }
        std::thread update_values([&]() {
            while (atomicActive) {
                std::this_thread::sleep_for(std::chrono::minutes(mainConfig.getInt64("update_values")));
                rolimons::ItemDB temporary = rolimons::getRolimonItems();
                for (auto asset = items["items"].MemberBegin(); asset != items["items"].MemberEnd(); ++asset) {
                    if (asset->value[5].GetInt() == -1)
                        continue;
                    temporary["items"][asset->name.GetString()][5].SetInt(asset->value[5].GetInt());
                }
                items = std::move(temporary);
            }
            });
        std::int64_t rolls = 0;
        while (atomicActive) {
            rolls++;
            if (rolls % 25 == 0)
                clear();
            std::cout << "Looking for a user to trade with...\n";
            atomic::User trader = USER_DEFAULT;
            try {
                trader = atomic::findUser(user, items);
            }
            catch (const atomic::HttpError& error) {
                std::cout << "Failed to find user, retrying...\n";
                std::this_thread::sleep_for(750ms);
                continue;
            }
            std::cout << "Creating a trade with " << trader.name() << " (" << trader.getId() << ")...\n";
            try {
                auto [offer, valueGain] = atomic::makeOffer(user.getInventory(items), trader.getInventory(items), mainConfig, items);
                roblox::sendTrade(user, atomic::Trade{ NULL, user, trader, offer, atomic::TradeType::Outbound });
                std::cout << "Trade created with a value gain of " << valueGain << "\n";
            }
            catch (const atomic::TradeFormFailure& tradeFailure) {
                std::cerr << "Failed to create a good trade with " << trader.name() << '\n';
                continue;
            }
            catch (const atomic::HttpError& httpError) {
                std::cerr << "Error occured while trying to send the trade, trade ratio may be too restricting...\n";
                continue;
            }
            std::cout << "Waiting " << mainConfig.getString("time_between_trade") << " seconds...\n";
            std::this_thread::sleep_for(std::chrono::seconds(mainConfig.getInt64("time_between_trade")));
        }
#ifndef VS_DEBUG
    }
    catch (const atomic::HttpError& error) {
        std::cerr << "An unhandled http error has occured: " << error.message << '\n';
    } catch (const atomic::ForbiddenError& error) {
        std::cerr << "An unhandled ForbiddenError has occured: " << error.message << '\n';
    } catch (...) {
        std::cerr << "An unhandled error has occured, restarting Atomic...\n";
    }
    std::this_thread::sleep_for(5s); // Give the user time to read the message
    release();
#endif
    return EXIT_SUCCESS;
}

int main() {
    if (isDebug)
        debug();
    else
        release();
}
