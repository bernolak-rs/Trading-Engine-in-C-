#pragma once
#include "price_bar.h"
#include "signal.h"
#include "portfolio.h"
#include <vector>

class Backtester {
    Portfolio portfolio_;

public:
    Backtester(double initial_cash) : portfolio_(initial_cash) {}

    void run(const std::vector<PriceBar>& bars,
             const std::vector<Signal>& signals);

    const Portfolio& portfolio() const { return portfolio_; }
};