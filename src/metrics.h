#pragma once
#include "types.h"
#include <vector>
using namespace std;

class Metrics {
    public:
    explicit Metrics(uint64_t initial_capital);

    Statistics calculate(const vector<Trade>& trades);

    private:
    uint64_t initial_capital_;
};

