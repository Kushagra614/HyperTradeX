#pragma once

#include <cstdint>

/* --- Better order (for cache):
All 64-bit fields together
All 32-bit fields together */
struct Kline
{
    uint64_t timestamp_ms;
    uint32_t symbol_id;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

struct Trade
{
    uint64_t trade_id;
    uint64_t entry_time_ms;
    uint64_t exit_time_ms;
    uint64_t entry_latency_us;
    uint64_t exit_latency_us;
    double entry_price;
    double exit_price;
    double quantity;
    double pnl;
};

struct Statistics
{
    uint64_t total_trades;
    uint64_t winning_trades;
    double total_pnl;
    double win_rate;
    double max_drawdown;
    double largest_win;
    double largest_loss;
    double avg_entry_latency_us;
    double avg_exit_latency_us;
    double p99_latency_us;
    double p50_latency_us;
};




