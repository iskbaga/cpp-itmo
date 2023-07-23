#include "PercolationStats.hpp"

#include <cmath>
#include <iostream>
#include <numeric>
#include <random>

#include "Percolation.hpp"

PercolationStats::PercolationStats(std::size_t size, std::size_t trials) : trials{trials}, size{size} {
    execute();
}

double PercolationStats::mean() const {
    return std::accumulate(results.begin(), results.end(), 0.0) / trials;
}

double PercolationStats::standardDeviation() const {
    double sum = 0;
    double m   = mean();
    for (std::size_t i = 0; i < trials; i++) {
        sum += (results[i] - m) * (results[i] - m);
    }
    return std::sqrt(sum / (trials - 1));
}

double PercolationStats::confidenceLow() const {
    double m = mean();
    double s = standardDeviation();
    return m - 1.96 * s / std::sqrt(trials);
}

double PercolationStats::confidenceHigh() const {
    double m = mean();
    double s = standardDeviation();
    return m + 1.96 * s / std::sqrt(trials);
}

void PercolationStats::execute() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    results.resize(trials);
    for (std::size_t t = 0; t < trials; ++t) {
        Percolation perc(size);
        while (!perc.hasPercolation()) {
            std::size_t row = dis(gen);
            std::size_t col = dis(gen);

            perc.open(row, col);
        }
        results[t] = static_cast<double>(perc.numberOfOpenCells()) / (size * size);
    }
}
