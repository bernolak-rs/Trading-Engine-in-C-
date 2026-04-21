#pragma once
#include "metrics.h"

class Reporter {
public:
    static void print(const MetricsResult& r);
};