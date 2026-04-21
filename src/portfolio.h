#pragma once
#include <string>
#include <vector>

struct Trade {
    std::string date;
    std::string type;// "BUY" or "SELL"
    double price;
    int shares;
    double cash_after;
};

class Portfolio {
    double cash_;
    int shares_held_;
    std::vector<Trade> history_;

public:
    Portfolio(double initial_cash)
        : cash_(initial_cash), shares_held_(0) {}

    void buy(const std::string& date, double price);
    void sell(const std::string& date, double price);

    double cash()        const { return cash_; }
    int    shares()      const { return shares_held_; }
    double equity(double current_price) const {
        return cash_ + shares_held_ * current_price;
    }

    const std::vector<Trade>& history() const { return history_; }
    void printSummary(double final_price) const;
};