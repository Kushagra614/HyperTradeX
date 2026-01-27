# Strategy Engine Implementation - Complete Teaching

## TEACHING: What is a Strategy?

### What Does a Strategy Do?

A strategy receives market data (klines) and makes trading decisions: **BUY, SELL, or HOLD**

**Example:**
```
Kline 1: close = 42550 → Strategy says: "BUY 1 BTC"
Kline 2: close = 42600 → Strategy says: "HOLD"
Kline 3: close = 42700 → Strategy says: "SELL 1 BTC"
```

---

## Simple Strategy for Phase 1

**Rule:** "Buy and hold for N seconds"

```
1. When position = empty: BUY
2. When position = open: Check if hold time expired
   - If YES: SELL
   - If NO: HOLD
3. Repeat
```

**Visual:**
```
Time:  0s     5s     10s    15s    20s
       |      |      |      |      |
Data:  K1     K2     K3     K4     K5
       BUY!   HOLD   HOLD   SELL!  BUY!
```

---

## State Machine Concept

A strategy has **states** (position is open or closed):

```
         ┌─────────────┐
         │  NO POSITION │ ← Start here
         └──────┬──────┘
                │ BUY decision
                ↓
         ┌─────────────┐
         │HAS POSITION │
         └──────┬──────┘
                │ Hold time expired?
                │ NO: wait
                │ YES: SELL
                ↓
         ┌─────────────┐
         │NO POSITION  │ ← Back to start
         └─────────────┘
```

---

## What Data Does Strategy Need?

```cpp
struct Strategy {
    uint64_t hold_duration_ms;     // How long to hold (e.g., 5000ms = 5s)
    
    uint64_t entry_time_ms;        // When did we buy?
    double entry_price;            // What price did we buy at?
    bool has_position;             // Do we have an open position?
};
```

**Why store this?**
- `entry_time_ms` → Check if enough time passed to sell
- `entry_price` → Track P&L (not used in Phase 1, but useful)
- `has_position` → Know what state we're in

---

## What Does Strategy Return?

```cpp
struct Decision {
    bool should_trade;   // Should we execute?
    bool is_buy;         // true = buy, false = sell
    uint64_t quantity;   // How many to trade
};
```

**Examples:**
```cpp
Decision d1 = {should_trade: true, is_buy: true, quantity: 1};    // BUY 1
Decision d2 = {should_trade: false, is_buy: false, quantity: 0};  // DO NOTHING
Decision d3 = {should_trade: true, is_buy: false, quantity: 1};   // SELL 1
```

---

## Algorithm

```
on_kline(kline):
  if has_position == false:
    // No position → BUY
    entry_time = kline.timestamp
    entry_price = kline.close
    has_position = true
    return Decision{should_trade: true, is_buy: true, quantity: 1}
  else:
    // Have position → Check if time to sell
    hold_time = kline.timestamp - entry_time
    
    if hold_time >= hold_duration:
      // Time to exit!
      has_position = false
      return Decision{should_trade: true, is_buy: false, quantity: 1}
    else:
      // Not yet
      return Decision{should_trade: false, is_buy: false, quantity: 0}
```

---

## Why State Machine?

**Without state machine (BAD):**
```cpp
if (kline.close > 42600) BUY;
else SELL;
// Problem: Always buying/selling! No positions held!
```

**With state machine (GOOD):**
```cpp
if (!has_position) BUY;
else if (hold_time_expired) SELL;
// Problem solved: Properly enters and exits trades
```

---

## strategy.h Header File

```cpp
#pragma once

#include "types.h"

using namespace std;

class Strategy {
public:
    struct Decision {
        bool should_trade = false;
        bool is_buy = false;
        uint64_t quantity = 0;
    };
    
    explicit Strategy(uint64_t hold_duration_ms);
    Decision on_kline(const Kline& kline);
    
private:
    uint64_t hold_duration_ms_;
    uint64_t entry_time_ms_ = 0;
    double entry_price_ = 0.0;
    bool has_position_ = false;
};
```

**Key Points:**
- `Decision` = nested struct (defined inside Strategy)
- `on_kline()` = called once per kline
- Private members track state

---

## strategy.cpp Implementation

```cpp
#include "strategy.h"

Strategy::Strategy(uint64_t hold_duration_ms)
    : hold_duration_ms_(hold_duration_ms) {}

Strategy::Decision Strategy::on_kline(const Kline& kline) {
    Decision decision;
    
    if (!has_position_) {
        // No position: BUY
        decision.should_trade = true;
        decision.is_buy = true;
        decision.quantity = 1;
        
        has_position_ = true;
        entry_time_ms_ = kline.timestamp_ms;
        entry_price_ = kline.close;
    } else {
        // Have position: Check if time to SELL
        uint64_t hold_time = kline.timestamp_ms - entry_time_ms_;
        
        if (hold_time >= hold_duration_ms_) {
            // Time to exit!
            decision.should_trade = true;
            decision.is_buy = false;
            decision.quantity = 1;
            
            has_position_ = false;
        }
        // else: decision stays {false, false, 0} → DO NOTHING
    }
    
    return decision;
}
```

---

## Step-by-Step Execution Example

### Initial State
```
has_position_ = false
entry_time_ms_ = 0
entry_price_ = 0.0
hold_duration_ms_ = 5000 (5 seconds)
```

### Kline 1 arrives (timestamp: 1704067200000, close: 42550)
```
on_kline(kline1):
  if (!has_position_)  // true, no position yet
    decision = {should_trade: true, is_buy: true, quantity: 1}
    has_position_ = true
    entry_time_ms_ = 1704067200000
    entry_price_ = 42550
  return decision
```

**Result:** BUY signal sent ✅

### Kline 2 arrives (timestamp: 1704067202000, close: 42600)
```
on_kline(kline2):
  if (!has_position_)  // false, we have position
    // Skip this block
  else:
    hold_time = 1704067202000 - 1704067200000 = 2000 ms
    if (2000 >= 5000)  // false, not enough time yet
      // Skip this block
    // decision stays {false, false, 0}
  return decision
```

**Result:** HOLD (no action) ✅

### Kline 3 arrives (timestamp: 1704067205000, close: 42680)
```
on_kline(kline3):
  if (!has_position_)  // false, we still have position
    // Skip this block
  else:
    hold_time = 1704067205000 - 1704067200000 = 5000 ms
    if (5000 >= 5000)  // true, time expired!
      decision = {should_trade: true, is_buy: false, quantity: 1}
      has_position_ = false
    // Skip else block
  return decision
```

**Result:** SELL signal sent ✅

### Kline 4 arrives (timestamp: 1704067206000, close: 42700)
```
on_kline(kline4):
  if (!has_position_)  // true again, position closed
    decision = {should_trade: true, is_buy: true, quantity: 1}
    has_position_ = true
    entry_time_ms_ = 1704067206000
    entry_price_ = 42700
  return decision
```

**Result:** BUY signal sent (new cycle) ✅

---

## Key Concepts

### 1. State Tracking
```cpp
has_position_      // Are we in a trade?
entry_time_ms_     // When did we enter?
entry_price_       // At what price?
```

### 2. Decision Structure
```cpp
struct Decision {
    bool should_trade;     // Execute or skip?
    bool is_buy;          // Direction
    uint64_t quantity;    // Size
};
```

### 3. Time-Based Exit
```cpp
uint64_t hold_time = kline.timestamp_ms - entry_time_ms_;
if (hold_time >= hold_duration_ms_) {
    // Exit
}
```

### 4. State Transition
```
NO_POSITION → (BUY) → HAS_POSITION → (time expires) → (SELL) → NO_POSITION
```

---

## How It Integrates

### In ReplayEngine Callback
```cpp
engine.replay([&](const Kline& kline) {
    // Strategy decides
    auto decision = strategy.on_kline(kline);
    
    if (decision.should_trade) {
        // Execution simulator fills the order
        auto trade = executor.execute(kline, decision);
        
        // Metrics tracks the trade
        metrics.record(trade);
    }
});
```

---

## Important Notes

### For Phase 1
- Simple buy-and-hold strategy
- No sophisticated logic
- Focus on understanding state machines

### For Phase 2+
- Can add complex logic:
  - Technical indicators (RSI, MACD, etc)
  - Multiple positions
  - Risk management (stop-loss, take-profit)
  - Portfolio rebalancing

### Memory & Performance
- No allocations in `on_kline()` ✅
- O(1) execution time ✅
- Good for high-frequency strategies

---

## Summary

| Aspect | What It Does |
|--------|-------------|
| **Input** | Kline (market data) |
| **Process** | Check state, decide action |
| **Output** | Decision (buy/sell/hold) |
| **State** | Position status, entry time, entry price |
| **Complexity** | O(1) - constant time |

