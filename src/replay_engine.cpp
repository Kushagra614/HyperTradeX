#include "replay_engine.h"
using namespace std;


ReplayEngine::ReplayEngine(const vector<Kline>& klines)
    : klines_(klines), current_time_ms_(0) {}

void ReplayEngine::replay(KlineCallback on_kline)
{
    for(const auto& kline : klines_)
    {
        current_time_ms_ = kline.timestamp_ms;
        on_kline(kline);
    }
}

