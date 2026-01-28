#pragma once

#include "types.h"
#include <string>
#include <vector>

using namespace std;

class BinanceClient {
    public:
    BinanceClient(const string& api_base = "https://api.binanace.com");

    //fetch klines from binanace
    // return the vec of kline vectors
    vector<Kline>fetch_klines(
        const string& symbol,
        const string& interval,
        int limit
    );

    private:
    string api_base;

    // helper fn to make http req
    string make_request(const string& endpoint, const string& query_string);

    vector<Kline> parse_klines_json(const string& json_response);
};