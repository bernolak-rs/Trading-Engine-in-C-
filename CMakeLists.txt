cmake_minimum_required(VERSION 3.15)
project(TradingEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(trading_engine 
    src/main.cpp
    src/data_loader.cpp
    src/smaindicator.cpp
    src/portfolio.cpp
    src/backtester.cpp
    src/metrics.cpp
    src/reporter.cpp
)

target_include_directories(trading_engine PRIVATE src)