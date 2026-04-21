#include "data_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<PriceBar> DataLoader::load(const std::string& filename) {
    std::vector<PriceBar> bars;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << "\n";
        return bars;
    }

    std::string line;
    std::getline(file, line); // skip first line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        PriceBar bar;

        std::getline(ss, bar.date, ',');
        std::getline(ss, token, ','); 
        bar.open = std::stod(token);
        std::getline(ss, token, ','); 
        bar.high = std::stod(token);
        std::getline(ss, token, ','); 
        bar.low = std::stod(token);
        std::getline(ss, token, ','); 
        bar.close = std::stod(token);
        std::getline(ss, token, ','); 
        bar.volume = std::stol(token);
        
        bars.push_back(bar);
    }
    return bars;
}
