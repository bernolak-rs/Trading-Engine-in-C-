#pragma once

#include <vector>

#include "price_bar.h"

class DataLoader {
    public:
        std::vector<PriceBar> load(const std::string& filename);
};