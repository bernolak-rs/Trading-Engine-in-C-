#include <iostream>
#include "data_loader.h"
#include "strategy.h"
#include "backtester.h"
#include "metrics.h"
#include "reporter.h"

int main() {
    const double INITIAL_CASH = 10000.0;

    // 1. load data
    DataLoader loader;
    auto bars = loader.load("../data/SPY.csv");

    if (bars.empty()) {
        std::cerr << "No data loaded. Check your CSV file.\n";
        return 1;
    }

    std::cout << "Loaded " << bars.size() << " bars ("
              << bars.front().date << " to "
              << bars.back().date  << ")\n\n";

    // 2. generate signals
    SMACrossover strategy(10, 50);
    auto signals = strategy.generateSignals(bars);

    // 3. run backtest
    Backtester backtester(INITIAL_CASH);
    backtester.run(bars, signals);

    // 4. compute & print metrics
    auto results = Metrics::compute(
        backtester.portfolio(), bars, INITIAL_CASH);
    Reporter::print(results);

    return 0;
}