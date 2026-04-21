#include "smaindicator.h"

std::vector<double> SMAIndicator::compute(const std::vector<PriceBar>& bars) const {
    std::vector<double> sma(bars.size(), 0.0);

    for (int i = this->period_ - 1; i < (int)bars.size(); ++i) {
        double sum = 0.0;
        for (int j = i - this->period_ + 1; j <= i; ++j) {
            sum += bars[j].close;
        }
        sma[i] = sum / period_;
    }
    return sma;
}