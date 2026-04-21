#pragma once
#include "portfolio.h"
#include "price_bar.h"
#include <vector>

struct MetricsResult {
    double total_return;        // % return on initial capital
    double buy_and_hold_return; // % return of just holding
    double sharpe_ratio;        // risk-adjusted return
    double max_drawdown;        // worst peak-to-trough drop %
    double win_rate;            // % of trades that were profitable
    int    total_trades;        // number of round trips (buy+sell pairs)
};

class Metrics {
public:
    static MetricsResult compute(
        const Portfolio& portfolio,
        const std::vector<PriceBar>& bars,
        double initial_cash
    );

private:
    static std::vector<double> buildEquityCurve(
        const Portfolio& portfolio,
        const std::vector<PriceBar>& bars,
        double initial_cash
    );

    static double computeSharpe(const std::vector<double>& equity_curve);
    static double computeMaxDrawdown(const std::vector<double>& equity_curve);
    static double computeWinRate(const std::vector<Trade>& history);
};