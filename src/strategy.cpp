#include "strategy.h"
using namespace std;

Strategy::Strategy(uint64_t hold_duration_ms)
    : hold_duration_ms_(hold_duration_ms),
      entry_time_ms_(0),
      entry_price_(0.0),
      has_position_(false) {}

Strategy::Decision Strategy::on_kline(const Kline& kline)
{
    Decision decision;

    if(!has_position_)
    {
        //no pos ->buy
        decision.should_trade = true;
        decision.is_buy = true;
        decision.quantity = 1;

        entry_time_ms_ = kline.timestamp_ms;
        entry_price_  = kline.close;
        has_position_ = true;
    }
    else{
        uint64_t hold_time = kline.timestamp_ms - entry_time_ms_;

        if(hold_time >= hold_duration_ms_)
        {
            //time to sell
            decision.should_trade = true;
            decision.is_buy = false;
            decision.quantity = 1;

            has_position_ = false;
        }
    }
    return decision;
}