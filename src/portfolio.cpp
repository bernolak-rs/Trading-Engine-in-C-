#include "portfolio.h"
#include <iostream>
#include <iomanip>

void Portfolio::buy(const std::string& date, double price) {
    if (shares_held_ > 0) return; // already in position, skip

    int shares_to_buy = static_cast<int>(cash_ / price);
    if (shares_to_buy <= 0) return;

    cash_ -= shares_to_buy * price;
    shares_held_ += shares_to_buy;

    history_.push_back({ date, "BUY", price, shares_to_buy, cash_ });

    std::cout << "BUY  " << shares_to_buy << " shares on "
              << date << " at $" << std::fixed << std::setprecision(2)
              << price << "  cash left: $" << cash_ << "\n";
}

void Portfolio::sell(const std::string& date, double price) {
    if (shares_held_ == 0) return; // nothing to sell, skip

    double proceeds = shares_held_ * price;
    cash_ += proceeds;

    history_.push_back({ date, "SELL", price, shares_held_, cash_ });

    std::cout << "SELL " << shares_held_ << " shares on "
              << date << " at $" << std::fixed << std::setprecision(2)
              << price << "  cash now:  $" << cash_ << "\n";

    shares_held_ = 0;
}

void Portfolio::printSummary(double final_price) const {
    std::cout << "\n===== PORTFOLIO SUMMARY =====\n";
    std::cout << "Trades executed : " << history_.size() << "\n";
    std::cout << "Shares held     : " << shares_held_ << "\n";
    std::cout << "Cash            : $" << std::fixed << std::setprecision(2)
              << cash_ << "\n";
    std::cout << "Total equity    : $" << equity(final_price) << "\n";
}