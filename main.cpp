#include "CurlRequest.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::string apiKey = "OmMyMTk0OThmYzA2ZWI5Njg2NjE2MmNiYjAxOTgxYTUz";
    std::string symbol = "AAPL";

    // The IEX Cloud endpoint for the latest stock quote
    std::string url = "https://api-v2.intrinio.com/securities/AAPL/prices?api_key=" + apiKey;

    CurlRequest curlRequest;
    std::string response = curlRequest.performGetRequest(url);
    if (!response.empty())
    {
        std::cout << "Response data: " << response << std::endl;
    }

    return 0;
}
