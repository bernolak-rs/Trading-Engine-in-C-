#include "metrics.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

std::vector<double> Metrics::buildEquityCurve(
    const Portfolio& portfolio,
    const std::vector<PriceBar>& bars,
    double initial_cash)
{
    std::vector<double> curve;
    curve.reserve(bars.size());

    double cash = initial_cash;
    int    shares = 0;
    int    trade_idx = 0;

    const auto& history = portfolio.history();

    for (const auto& bar : bars) {
        // apply any trades that happened on this bar
        while (trade_idx < (int)history.size() &&
               history[trade_idx].date == bar.date) {
            const auto& t = history[trade_idx];
            if (t.type == "BUY") {
                shares = t.shares;
                cash   = t.cash_after;
            } else {
                shares = 0;
                cash   = t.cash_after;
            }
            ++trade_idx;
        }
        curve.push_back(cash + shares * bar.close);
    }

    return curve;
}

double Metrics::computeSharpe(const std::vector<double>& equity_curve) {
    if (equity_curve.size() < 2) return 0.0;

    std::vector<double> returns;
    returns.reserve(equity_curve.size() - 1);
    for (int i = 1; i < (int)equity_curve.size(); ++i) {
        if (equity_curve[i-1] > 0)
            returns.push_back((equity_curve[i] - equity_curve[i-1])
                              / equity_curve[i-1]);
    }

    double mean = std::accumulate(returns.begin(), returns.end(), 0.0)
                  / returns.size();

    double variance = 0.0;
    for (double r : returns)
        variance += (r - mean) * (r - mean);
    variance /= returns.size();

    double std_dev = std::sqrt(variance);
    if (std_dev == 0.0) return 0.0;

    auto trading_days = 252.0;
    return (mean / std_dev) * std::sqrt(trading_days);
}

double Metrics::computeMaxDrawdown(const std::vector<double>& equity_curve) {
    double peak        = equity_curve.front();
    double max_dd      = 0.0;

    for (double val : equity_curve) {
        if (val > peak) peak = val;
        double dd = (peak - val) / peak;
        if (dd > max_dd) max_dd = dd;
    }

    return max_dd * 100.0; // as percentage
}

double Metrics::computeWinRate(const std::vector<Trade>& history) {
    int wins  = 0;
    int total = 0;

    // pair up BUY/SELL round trips
    for (int i = 0; i + 1 < (int)history.size(); i += 2) {
        if (history[i].type == "BUY" && history[i+1].type == "SELL") {
            if (history[i+1].price > history[i].price) ++wins;
            ++total;
        }
    }

    return total > 0 ? (double)wins / total * 100.0 : 0.0;
}

MetricsResult Metrics::compute(
    const Portfolio& portfolio,
    const std::vector<PriceBar>& bars,
    double initial_cash)
{
    auto curve = buildEquityCurve(portfolio, bars, initial_cash);

    double final_equity    = curve.back();
    double total_return    = (final_equity - initial_cash) / initial_cash * 100.0;

    double bnh_shares      = initial_cash / bars.front().close;
    double bnh_final       = bnh_shares * bars.back().close;
    double bnh_return      = (bnh_final - initial_cash) / initial_cash * 100.0;

    MetricsResult result;
    result.total_return        = total_return;
    result.buy_and_hold_return = bnh_return;
    result.sharpe_ratio        = computeSharpe(curve);
    result.max_drawdown        = computeMaxDrawdown(curve);
    result.win_rate            = computeWinRate(portfolio.history());
    result.total_trades        = (int)portfolio.history().size() / 2;

    return result;
}