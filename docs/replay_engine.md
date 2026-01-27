# Replay Engine Implementation - Complete Teaching

## TEACHING: What is a Replay Engine?

### The Problem

You have 20 klines (candlesticks) in your CSV file:

```
Kline 1: timestamp=1704067200000, close=42550
Kline 2: timestamp=1704067260000, close=42600
Kline 3: timestamp=1704067320000, close=42680
...
Kline 20: timestamp=1704068340000, close=42900
```

You want to **simulate trading** by going through these klines one by one, as if time is progressing.

**But how do you do that?**

---

### The Solution: Replay Engine

The Replay Engine **emits klines one at a time** in chronological order, like rewinding and replaying a recorded event.

**Real-world analogy:**
- Imagine you're watching a sports game
- You have a video recording of the entire game
- A **replay engine** lets you watch it frame-by-frame
- Frame 1, Frame 2, Frame 3... in order

---

## What Does Replay Engine Do? (Step by Step)

### Step 1: Initialize
```cpp
ReplayEngine engine(klines);
// Stores all 20 klines
// Sets current_time = 0
```

### Step 2: Start Replaying
```cpp
engine.replay(callback_function);
```

### Step 3: For Each Kline
```
Iteration 1: Call callback with Kline 1 (timestamp=1704067200000)
Iteration 2: Call callback with Kline 2 (timestamp=1704067260000)
Iteration 3: Call callback with Kline 3 (timestamp=1704067320000)
...
Iteration 20: Call callback with Kline 20 (timestamp=1704068340000)
```

**The callback** is what happens when each kline arrives. This is where your **strategy** runs!

---

## Visual Example

```
Timeline of Market Data:
|------|------|------|------|------|
T1     T2     T3     T4     T5     T6
Kline1 Kline2 Kline3 Kline4 Kline5 Kline6

Replay Engine:
1. current_time = T1, emit Kline1 → Strategy says: BUY!
2. current_time = T2, emit Kline2 → Strategy says: HOLD
3. current_time = T3, emit Kline3 → Strategy says: HOLD
4. current_time = T4, emit Kline4 → Strategy says: SELL!
5. current_time = T5, emit Kline5 → Strategy says: BUY!
6. current_time = T6, emit Kline6 → Strategy says: HOLD
```

---

## Why Do We Need It?

### Without Replay Engine (BAD)
```cpp
// In main.cpp
for (int i = 0; i < klines.size(); i++) {
    current_kline = klines[i];
    // Call strategy
    // Call execution
    // Call metrics
    // ... messy, hardcoded loop
}
```

### With Replay Engine (GOOD)
```cpp
// In main.cpp
engine.replay([&](const Kline& kline) {
    // Strategy
    // Execution
    // Metrics
    // ... clean, separated concerns
});
```

### Benefits
- ✅ Cleaner code (separation of concerns)
- ✅ Flexible (can swap callbacks)
- ✅ Testable (can test replay independently)
- ✅ Realistic (simulates real-time events)
- ✅ Deterministic (same input = same output)

---

## Key Concepts

### 1. Virtual Time
```cpp
// Real time (when you run the backtest): 2 seconds
// Virtual time (inside simulation): 20 minutes of market data
// Replay engine tracks virtual time!
```

### 2. Callbacks (Lambda Functions)
```cpp
// A callback = a function passed as parameter
engine.replay([&](const Kline& kline) {
    // This code runs for EACH kline
    cout << "Processing kline at " << kline.timestamp_ms << endl;
});
```

The `[&]` is a **lambda** - an inline function that captures all variables by reference.

### 3. Sequential Order
```cpp
// MUST process klines in order
// Kline 1 → Kline 2 → Kline 3 (not randomly!)
// Otherwise backtest is unrealistic and incorrect
```

### 4. std::function<> Type
```cpp
using KlineCallback = function<void(const Kline&)>;
// Defines a callback signature:
// - Takes: const Kline&
// - Returns: void
// - Can be any function matching this signature
```

---

## Simple Example in Pseudocode

```cpp
ReplayEngine {
    private:
        vector<Kline> klines_;
        uint64_t current_time_ms_;
    
    public:
        function replay(callback) {
            for each kline in klines_ {
                current_time_ms_ = kline.timestamp_ms
                callback(kline)  // Call with this kline
            }
        }
}

In main.cpp:
engine.replay([&](const Kline& kline) {
    decision = strategy.on_kline(kline)
    if (decision.should_trade) {
        trade = executor.execute(decision)
        metrics.record(trade)
    }
});
```

---

## replay_engine.h Header File

```cpp
#pragma once

#include "types.h"
#include <vector>
#include <functional>

using namespace std;

class ReplayEngine {
public:
    // Define callback signature: takes Kline, returns void
    using KlineCallback = function<void(const Kline&)>;
    
    // Constructor: takes vector of klines
    explicit ReplayEngine(const vector<Kline>& klines);
    
    // Main replay function: emits each kline to callback
    void replay(KlineCallback on_kline);
    
    // Get current virtual time
    uint64_t current_time_ms() const { return current_time_ms_; }
    
private:
    vector<Kline> klines_;
    uint64_t current_time_ms_ = 0;
};
```

**Key Points:**
- `using KlineCallback` = type alias for callback signature
- `explicit` constructor = prevents accidental implicit conversions
- `const` in getter = doesn't modify object state
- `private:` members = only ReplayEngine can access

---

## replay_engine.cpp Implementation

```cpp
#include "replay_engine.h"

// Constructor: store klines
ReplayEngine::ReplayEngine(const vector<Kline>& klines) 
    : klines_(klines), current_time_ms_(0) {}

// Main replay function
void ReplayEngine::replay(KlineCallback on_kline) {
    for (const auto& kline : klines_) {
        // Update virtual time
        current_time_ms_ = kline.timestamp_ms;
        
        // Emit kline to callback (strategy, execution, metrics run here)
        on_kline(kline);
    }
}
```

**How It Works:**
1. Loop through all klines
2. Update `current_time_ms_` to kline's timestamp
3. Call the callback function with current kline
4. Callback executes strategy, execution, metrics logic
5. Move to next kline
6. Repeat until all klines processed

---

## Lambda Functions (Callbacks) Explained

### What is a Lambda?

A **lambda** is a small, unnamed function you can define inline.

### Syntax
```cpp
[capture](parameters) -> return_type {
    // function body
}
```

### Example 1: Simple Lambda
```cpp
auto add = [](int a, int b) {
    return a + b;
};
cout << add(2, 3);  // Output: 5
```

### Example 2: Lambda with Capture
```cpp
int multiplier = 3;

auto multiply = [multiplier](int x) {
    return x * multiplier;
};

cout << multiply(5);  // Output: 15 (5 * 3)
```

### Example 3: Lambda in ReplayEngine (Our Case)
```cpp
engine.replay([&](const Kline& kline) {
    // [&] = capture all variables by reference
    // (const Kline& kline) = parameter
    // Body: strategy, execution, metrics
});
```

---

## Capture Modes

| Capture | Meaning | Use Case |
|---------|---------|----------|
| `[&]` | Capture all by reference | Need to modify external variables |
| `[=]` | Capture all by value | Want independent copy |
| `[&x]` | Capture x by reference | Only need specific variable |
| `[=x]` | Capture x by value | Only need copy of x |
| `[]` | Capture nothing | No external dependencies |

---

## Performance Considerations

### Why Replay Engine is Efficient

1. **No Allocations**
   - Klines already in memory (vector)
   - Just iterating (no new allocations)

2. **Sequential Access**
   - Klines stored in order
   - Good cache locality (CPU prefetches next kline)
   - Memory access is predictable

3. **Virtual Time Only**
   - No actual sleep/wait
   - No thread synchronization overhead
   - Backtests complete instantly

### Time Complexity
- **Space:** O(n) where n = number of klines
- **Time:** O(n) - must process each kline once

---

## Integration with Other Components

### Flow Chart
```
ReplayEngine emits each kline
        ↓
    Callback receives kline
        ↓
    Strategy.on_kline(kline) → Decision
        ↓
    Execution.execute(decision) → Trade
        ↓
    Metrics.record(trade)
        ↓
    Next kline (loop repeats)
```

### In main.cpp
```cpp
ReplayEngine engine(klines);

engine.replay([&](const Kline& kline) {
    // Strategy
    auto decision = strategy.on_kline(kline);
    
    if (decision.should_trade) {
        // Execution
        auto trade = executor.execute(kline, decision);
        
        // Metrics
        metrics.record(trade);
    }
});
```

---

## Why This Matters

1. **Deterministic Backtesting**
   - Same klines → same results
   - Reproducible simulations

2. **Separation of Concerns**
   - ReplayEngine doesn't care about strategy
   - Strategy doesn't care about execution
   - Each component has one job

3. **Easy Testing**
   - Can test ReplayEngine independently
   - Can test callbacks with mock klines
   - Clear interface (replay function)

4. **Foundation for Phase 2**
   - In Phase 2 (threading), we can emit klines from different threads
   - Same interface, different implementation

---

## Summary Table

| Aspect | What It Does |
|--------|-------------|
| **Input** | Vector of Kline structs (sorted by timestamp) |
| **Process** | Loop through klines in order, update virtual time |
| **Output** | Emit each kline to callback function |
| **State** | Maintains current_time_ms_ (virtual clock) |
| **Callback** | Function that processes each kline (strategy/execution/metrics) |

