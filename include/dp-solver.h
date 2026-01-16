#pragma once

#include "solver.h" // Assuming the interface is in this file
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class DPSolver : public SubsetSumSolver {
public:
    std::string getAlgorithmName() const override;

    /**
     * Solves the subset sum problem.
     * NOTE: This approach has a space complexity of O(Target).
     * It works best for small to medium targets (e.g., < 10^7).
     * For very large targets, this approach may run out of memory.
     */
    long long solve(const std::vector<long long>& numbers, long long target) override;
};