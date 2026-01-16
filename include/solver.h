#pragma once

#include <string>
#include <vector>

class SubsetSumSolver {
public:
    virtual ~SubsetSumSolver() = default;

    // Returns the name of the algorithm used by the solver
    virtual std::string getAlgorithmName() const = 0;

    // Solves the subset sum problem and returns the closest sum to the target
    virtual long long solve(const std::vector<long long> &numbers, long long target) = 0;
};