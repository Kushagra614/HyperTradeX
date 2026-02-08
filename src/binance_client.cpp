#include "binance_client.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <chrono>

using namespace std;
using json = nlohmann::json;

static size_t write_callback(void* contents, size_t size, size_t nmemb, string* userp)
{
    // size = bytes per item, nmemb = number of items
    // Total bytes = size * nmemb

    userp->append((char*)contents, size * nmemb);

    return size*nmemb;
}

string BinanceClient::make_request(const string& endpoint, const string& query_string)
{
    // initilaise curl
    CURL* curl = curl_easy_init();
    if(!curl)
    {
        throw::runtime_error("Failed to initialise CURL");
    }

    string url = api_base + endpoint+ query_string;

    // response_data starts empty, then write_callback() appends data to it
    // So it grows as data arrives
    string response_data;

    // setting the url
    curl_easy_setopt(          // "Set option"
    curl,                   // On this CURL handle
    CURLOPT_URL,           // Option: set the URL
    url.c_str()            // Value: the URL (converting into C string)
    );

    // set timeout
    // 10L -> 10 sec ( l => long integer) Wait max 10 seconds
    curl_easy_setopt (curl, CURLOPT_TIMEOUT, 10L); 


    // follow redirects
    // 1 = true, 0 = false
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // set callback function
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    // pass data to callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    //performing he http request
    CURLcode res = curl_easy_perform(curl);

    //check if the req succeeded
    if(res != CURLE_OK)
    {
        string error_msg = "CURL request Failed: " + string(curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        throw runtime_error(error_msg);
    }

    //check HTTP status code
    long http_code = 0;
    curl_easy_getinfo(
    curl,                          // Get info from this CURL handle
    CURLINFO_RESPONSE_CODE,        // I want: HTTP response code
    &http_code                     // Store result here (address)
);

if(http_code != 200)
{
    string error_msg = "HTTP error code: " + to_string(http_code);
    curl_easy_cleanup(curl);
    throw::runtime_error(error_msg);
}

curl_easy_cleanup(curl);

return response_data;


}

vector<Kline>BinanceClient::fetch_klines(
    const string& symbol,
    const string& interval,
    int limit
)
{
    //s1 -> building the query string
    // Example: "?symbol=BTCUSDT&interval=1m&limit=100"
    string query_string = 
        "?symbol=" + symbol +
        "&interval=" + interval +
        "&limit=" + to_string(limit);

    //s2 -> measuring the latency
    auto start = chrono::high_resolution_clock::now();

    // s3 -> making the http request
    string json_response = make_request("/api/v3/klines", query_string);

    auto end = chrono::high_resolution_clock::now();
    auto latency_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // s4-> printing the latency
    cout<< "API Latency" << latency_us<<" us (" << (latency_us / 1000 ) << " ms)"<<endl;

    //s5-> parse the json into Kline objects
    vector<Kline> klines = parse_klines_json(json_response);

    // s6 -> return the klines
    return klines;
     
}

vector<Kline>BinanceClient::parse_klines_json(const string& json_response)
{
    vector<Kline>klines;
    try{
        json parsed = json::parse(json_response);
    

    for(const auto& kline_array : parsed)
    {
        uint64_t timestamp_ms = kline_array[0].get<uint64_t>();
        double open = stod(kline_array[1].get<string>());
    }
} catch(...){ }
return klines;
}



BinanceClient::BinanceClient(const string& api_base) 
    : api_base(api_base) {}

