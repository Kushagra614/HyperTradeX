#pragma once

#include <vector>
#include <functional>
#include "types.h"

using namespace std;

class ReplayEngine {
public:
    using KlineCallback = function<void(const Kline&)>;
    
    explicit ReplayEngine(const vector<Kline>& klines);
    void replay(KlineCallback on_kline);
    uint64_t current_time_ms() const { return current_time_ms_; }
    
private:
    vector<Kline> klines_;
    uint64_t current_time_ms_ = 0;
};