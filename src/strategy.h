#pragma once

#include<types.h>
using namespace std;

class Strategy{
    public:
    struct Decision
    {
        bool should_trade;
        bool is_buy;
        uint64_t quantity;
    };

    explicit Strategy(uint64_t hold_duration_ms);
    Decision on_kline(const Kline& kline);

    private:
    uint64_t hold_duration_ms_;
    uint64_t entry_time_ms_;
    double entry_price_;
    bool has_position_;

};