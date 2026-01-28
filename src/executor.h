#pragma once
#include "types.h"
#include "strategy.h"
#include <optional>
using namespace std;

class Executor{

    public:
    explicit Executor(uint64_t initial_capital);
    
    optional<Trade> on_kline(const Kline& kline, const Strategy::Decision& decision);
    bool has_position() const;

    private:
    uint64_t entry_time_ms_;
    uint64_t quantity_;
    uint64_t next_trade_id_;
    double initial_capital_;
    double initial_price_;
    double entry_price_;
    bool has_position_;

};

