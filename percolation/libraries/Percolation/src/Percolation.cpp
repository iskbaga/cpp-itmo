#include "Percolation.hpp"

#include <stack>

Percolation::Percolation(std::size_t dimension)
    : cell(dimension, std::vector<CELL>(dimension, BLOCKED)), size{dimension} {}

void Percolation::open(std::size_t row, std::size_t column) {
    if (cell[row][column] == CELL::BLOCKED) {
        cell[row][column] = CELL::EMPTY;
        openCount++;
        if (row == 0) {
            dfs(row, column);
        } else if (isFull(row - 1, column)) {
            dfs(row, column);
        } else if (column > 0 && isFull(row, column - 1)) {
            dfs(row, column);
        } else if (column + 1 < size && isFull(row, column + 1)) {
            dfs(row, column);
        } else if (row + 1 < size && isFull(row + 1, column)) {
            dfs(row, column);
        }
    }
}

bool Percolation::isOpen(std::size_t row, std::size_t column) const {
    return cell[row][column] == CELL::EMPTY || cell[row][column] == CELL::FULL;
}

bool Percolation::isFull(std::size_t row, std::size_t column) const {
    return cell[row][column] == CELL::FULL;
}

std::size_t Percolation::numberOfOpenCells() const {
    return openCount;
}

bool Percolation::hasPercolation() const {
    return hasPerc;
}

void Percolation::dfs(std::size_t row, std::size_t column) {
    std::stack<std::pair<std::size_t, std::size_t>> stack;
    stack.push(std::make_pair(row, column));

    while (!stack.empty()) {
        std::pair<std::size_t, std::size_t> current = stack.top();
        stack.pop();

        std::size_t currentRow    = current.first;
        std::size_t currentColumn = current.second;

        cell[currentRow][currentColumn] = CELL::FULL;
        if (currentRow == size - 1) {
            hasPerc = true;
        }
        if (currentRow > 0 && isOpen(currentRow - 1, currentColumn) && !isFull(currentRow - 1, currentColumn)) {
            stack.push(std::make_pair(currentRow - 1, currentColumn));
        }
        if (currentColumn > 0 && isOpen(currentRow, currentColumn - 1) && !isFull(currentRow, currentColumn - 1)) {
            stack.push(std::make_pair(currentRow, currentColumn - 1));
        }
        if (currentColumn + 1 < size && isOpen(currentRow, currentColumn + 1) &&
            !isFull(currentRow, currentColumn + 1)) {
            stack.push(std::make_pair(currentRow, currentColumn + 1));
        }
        if (currentRow + 1 < size && isOpen(currentRow + 1, currentColumn) && !isFull(currentRow + 1, currentColumn)) {
            stack.push(std::make_pair(currentRow + 1, currentColumn));
        }
    }
}