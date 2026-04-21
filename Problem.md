A C++ program that reads historical price data, computes trading signals, simulates trades, and reports P&L — essentially a mini backtester focused on one strategy.

Phase 1 — Foundation (C++ skills: classes, vectors, file I/O)
Goal: Load price data and compute a simple moving average (SMA) crossover signal.

PriceBar struct: open, high, low, close, volume, timestamp
DataLoader class: reads CSV price data into a std::vector<PriceBar>
SMAIndicator class: computes rolling averages
Signal logic: buy when fast SMA crosses above slow SMA, sell when it crosses below

New C++ you'll learn: std::vector, std::ifstream, operator overloading, constructors

Phase 2 — Strategy & Portfolio (C++ skills: inheritance, STL maps)
Goal: Abstract the strategy so you can swap it out easily.

Abstract base class Strategy with a virtual generateSignal() method
SMACrossover inherits from Strategy
Portfolio class: tracks cash, positions, trade history using std::map
Simulate trades tick by tick through your historical data

New C++ you'll learn: virtual functions, polymorphism, std::map, std::unordered_map

Phase 3 — Risk & Reporting (C++ skills: algorithms, lambdas)
Goal: Measure how good your strategy is.

Compute Sharpe ratio, max drawdown, win rate
Use std::sort, std::accumulate, lambdas for calculations
Print a clean performance report to console or CSV

New C++ you'll learn: <algorithm>, lambdas, std::numeric_limits

Phase 4 — Stretch Goals (quant dev flavour)
Once the above is solid, these will impress on a CV:

Add a second strategy (RSI, Bollinger Bands) and compare them
Optimize parameters using a simple grid search
Move to std::chrono for proper timestamps
Introduce basic concurrency (std::thread) to run strategies in parallel