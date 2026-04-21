#pragma once
#include "price_bar.h"
#include "signal.h"
#include "smaindicator.h"
#include <vector>

class SMACrossover {
    SMAIndicator fastSMA_;
    SMAIndicator slowSMA_;
    int fastPeriod_;
    int slowPeriod_;
public:
    SMACrossover(int fastPeriod, int slowPeriod)
        : fastSMA_(fastPeriod), slowSMA_(slowPeriod), 
          fastPeriod_(fastPeriod), slowPeriod_(slowPeriod) {}

    std::vector<Signal> generateSignals(const std::vector<PriceBar>& bars) const {
        auto fast = fastSMA_.compute(bars);
        auto slow = slowSMA_.compute(bars);

        std::vector<Signal> signals(bars.size(), Signal::HOLD);

        int start = std::max(fastPeriod_, slowPeriod_);
        for (int i = start; i < (int)bars.size(); ++i) {
            if (fast[i] > slow[i] && fast[i-1] <= slow[i-1]) {
                signals[i] = Signal::BUY;
            } else if (fast[i] < slow[i] && fast[i-1] >= slow[i-1]) {
                signals[i] = Signal::SELL;
            }
        }

        return signals;
    }
};