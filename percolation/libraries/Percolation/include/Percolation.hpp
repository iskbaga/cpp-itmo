#ifndef PERCOLATION_HPP
#define PERCOLATION_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

struct Percolation {
public:
    /**
     * Construct a new Percolation object
     * @param dimension dimension of percolation table
     */
    Percolation(std::size_t dimension);

    /**
     * Opens the cell[row, column] if it's not opened already
     * @param row row index
     * @param column column index
     */
    void open(std::size_t row, std::size_t column);

    /**
     * Checks if cell[row, column] is open
     * @param row row index
     * @param column column index
     * @return true cell is open
     * @return false cell is blocked
     */
    [[nodiscard]] bool isOpen(std::size_t row, std::size_t column) const;

    /**
     * Checks if cell[row, column] is full
     * @param row row index
     * @param column column index
     * @return true cell is full
     * @return false cell is not full
     */
    [[nodiscard]] bool isFull(std::size_t row, std::size_t column) const;

    /**
     * Gets number of open cells in table
     * @return number of open cells
     */
    [[nodiscard]] std::size_t numberOfOpenCells() const;

    /**
     * Checks if system percolates
     * @return true system percolates
     * @return false system doesn't percolate
     */
    [[nodiscard]] bool hasPercolation() const;

private:
    enum CELL { BLOCKED, EMPTY, FULL };
    std::vector<std::vector<CELL>> cell;
    bool hasPerc = false;
    std::size_t size;
    std::size_t openCount = 0;
    void dfs(size_t row, size_t column);
};
#endif  // PERCOLATION_HPP