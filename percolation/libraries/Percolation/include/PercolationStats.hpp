#ifndef PERCOLATIONSTATS_HPP
#define PERCOLATIONSTATS_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

struct PercolationStats {
public:
    /**
     * Construct a new Percolation Stats object
     * @param size size of percolation grid
     * @param trials amount of experiments
     */
    PercolationStats(std::size_t size, std::size_t trials);

    /**
     * Returns mean of percolation threshold (x¯ from description)
     */
    [[nodiscard]] double mean() const;

    /**
     * Returns standard deviation of percolation threshold (s from description)
     */
    [[nodiscard]] double standardDeviation() const;

    /**
     * Returns log edge of condidence interval
     */
    [[nodiscard]] double confidenceLow() const;

    /**
     * Returns high edge of confidence interval
     */
    [[nodiscard]] double confidenceHigh() const;

    /**
     * Makes all experiments, calculates statistic values
     */
    void execute();

private:
    std::size_t trials;
    std::size_t size;
    std::vector<double> results;
};

#endif  // PERCOLATIONSTATS_HPP