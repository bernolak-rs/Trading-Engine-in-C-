#include "backtester.h"
#include <iostream>

void Backtester::run(const std::vector<PriceBar>& bars,
                     const std::vector<Signal>& signals) {
    for (int i = 0; i < (int)bars.size(); ++i) {
        const auto& bar = bars[i];

        if (signals[i] == Signal::BUY) {
            portfolio_.buy(bar.date, bar.close);
        } else if (signals[i] == Signal::SELL) {
            portfolio_.sell(bar.date, bar.close);
        }
    }
}