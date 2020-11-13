#include <string>
#include <regex>
#include "./Conversion.h"
#include "./rapidjson/document.h"
#include "./rapidjson/stringbuffer.h"
#include "./rapidjson/writer.h"

[[nodiscard]] std::string atomic::formatCookie(const std::string& cookie) {
	const std::regex pattern{R"(_\|[\D\d]+\|_)"};
	return std::regex_replace(cookie, pattern, "");
}

[[nodiscard]] std::string atomic::tradeToJSON(const atomic::AuthUser& user, const atomic::Trade& trade) {
	const char* tradeStructure = R"(
    {
       "offers":[
          {
             "userId": 0,
             "userAssetIds":[],
             "robux": 0
          },
          {
             "userId": 0,
             "userAssetIds":[],
             "robux": 0
          }
       ]
    }
)";
    rapidjson::Document d;
    d.Parse(tradeStructure);
    d["offers"][0]["userId"].SetInt64(trade.getTrader().getId());
    d["offers"][1]["userId"].SetInt64(user.getId());
    d["offers"][0]["robux"].SetInt(trade.getOffer().getRobuxRequested());
    d["offers"][1]["robux"].SetInt(trade.getOffer().getRobuxOffered());
    auto offering = trade.getOffer().getOffering();
    auto requesting = trade.getOffer().getRequesting();
    for (auto item = offering.begin(); item != offering.end(); ++item) {
        if (item->userAssetId != 0) {
            d["offers"][1]["userAssetIds"].PushBack(item->userAssetId, d.GetAllocator());
        }
    }
    for (auto item = requesting.begin(); item != requesting.end(); ++item) {
        if (item->userAssetId != 0) {
            d["offers"][0]["userAssetIds"].PushBack(item->userAssetId, d.GetAllocator());
        }
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    return buffer.GetString();
}