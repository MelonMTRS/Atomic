#include <string>
#include <regex>
#include "./Conversion.h"
#include "./rapidjson/document.h"

[[nodiscard]] std::string atomic::formatCookie(std::string cookie) {
	std::regex pattern{R"(_\|[\D\d]+\|_)"};
	return std::regex_replace(cookie, pattern, "");
}

[[nodiscard]] std::string atomic::tradeToJSON(atomic::AuthUser& user, atomic::Trade trade) {
	std::string structure = R"(
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
    d.Parse(structure.c_str());
    d["offers"][0]["userId"].SetInt64(trade.getTrader().getId());
    d["offers"][1]["userId"].SetInt64(user.getId());
    auto offering = trade.getOffer().getOffering();
    auto requesting = trade.getOffer().getRequesting();
    for (auto item = offering.begin(); item != offering.end(); ++item) {
        // TODO: Push back to d["offers"][0]["userAssetIds"]
    }
    for (auto item = requesting.begin(); item != requesting.end(); ++item) {
        // TODO: Push back to d["offers"][1]["userAssetIds"]
    }
    return ""; // Temporary
}