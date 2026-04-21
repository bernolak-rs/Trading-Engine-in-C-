#pragma once

#include <vector>

#include "price_bar.h"

class SMAIndicator {
    int period_;
public:
    SMAIndicator(int period) : period_(period) {}
    std::vector<double> compute(const std::vector<PriceBar>& bars) const;
};