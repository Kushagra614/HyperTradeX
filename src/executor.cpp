#include "executor.h"
#include <chrono>
using namespace std;


Executor::Executor(uint64_t initial_capital)
    : entry_time_ms_(0),
      entry_latency_us_(0),
      exit_latency_us_(0),
      quantity_(0),
      next_trade_id_(0),
      initial_price_(static_cast<double>(initial_capital)),
      entry_price_(0.0),
      has_position_(false) {}

bool Executor::has_position() const {
    return has_position_;
}

optional<Trade> Executor::on_kline(const Kline& kline, const Strategy::Decision& decision) {
    // If strategy says don't trade, return nothing
    if (!decision.should_trade) {
        return nullopt;
    }
    
    // BUYING: Enter a position
    if (decision.is_buy) {
        entry_price_ = kline.close;
        entry_time_ms_ = kline.timestamp_ms;
        quantity_ = decision.quantity;
        has_position_ = true;
        // Record current time in microseconds for latency calculation
        auto now = chrono::high_resolution_clock::now();
        uint64_t exec_time_us = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
        entry_latency_us_ = exec_time_us - kline.fetch_time_ms;
        return nullopt;  // Trade not complete yet
    }
    
    // SELLING: Close the position
    double exit_price = kline.close;
    uint64_t exit_time = kline.timestamp_ms;
    double pnl = (exit_price - entry_price_) * static_cast<double>(quantity_);
    // Record current time in microseconds for latency calculation
    auto now_exit = chrono::high_resolution_clock::now();
    uint64_t exec_time_us_exit = chrono::duration_cast<chrono::microseconds>(now_exit.time_since_epoch()).count();
    exit_latency_us_ = exec_time_us_exit - kline.fetch_time_ms;
    
    // Create completed Trade
    Trade completed_trade = {
        next_trade_id_,                      // trade_id
        entry_time_ms_,                      // entry_time_ms
        exit_time,                           // exit_time_ms
        entry_latency_us_,                   // entry_latency_us
        exit_latency_us_,                    // exit_latency_us
        entry_price_,                        // entry_price
        exit_price,                          // exit_price
        static_cast<double>(quantity_),      // quantity (cast to double)
        pnl                                  // pnl
    };
    
    // Update state
    has_position_ = false;
    next_trade_id_++;
    
    return completed_trade;
}

