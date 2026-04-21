#pragma once

#include <string>

struct PriceBar
{
    /* data */
    std::string date;
    double open, high, low, close;
    long volume;
};
