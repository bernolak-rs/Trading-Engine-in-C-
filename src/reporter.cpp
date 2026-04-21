#include "reporter.h"
#include <iostream>
#include <iomanip>

void Reporter::print(const MetricsResult& r) {
    auto pct = [](double v) {
        return (v >= 0 ? "+" : "") + std::to_string(v).substr(0, 6) + "%";
    };

    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║        PERFORMANCE REPORT            ║\n";
    std::cout << "╠══════════════════════════════════════╣\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "║  Strategy return   : " << std::setw(8)
              << r.total_return        << "%       ║\n";
    std::cout << "║  Buy-and-hold      : " << std::setw(8)
              << r.buy_and_hold_return << "%       ║\n";
    std::cout << "║  Sharpe ratio      : " << std::setw(8)
              << r.sharpe_ratio        << "        ║\n";
    std::cout << "║  Max drawdown      : " << std::setw(8)
              << r.max_drawdown        << "%       ║\n";
    std::cout << "║  Win rate          : " << std::setw(8)
              << r.win_rate            << "%       ║\n";
    std::cout << "║  Round trips       : " << std::setw(8)
              << r.total_trades        << "        ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";

    std::cout << "\nVerdict: ";
    if (r.total_return > r.buy_and_hold_return && r.sharpe_ratio > 0.5)
        std::cout << "Strategy BEATS buy-and-hold ✓\n";
    else if (r.total_return > 0)
        std::cout << "Strategy is profitable but TRAILS buy-and-hold\n";
    else
        std::cout << "Strategy UNDERPERFORMS — tune your parameters\n";
}