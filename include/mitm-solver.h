#pragma once

#include "solver.h"
#include <vector>
#include <utility> // for std::pair

class MITMSolver : public SubsetSumSolver {
public:
    std::string getAlgorithmName() const override;

    long long solve(const std::vector<long long>& numbers, long long target) override;

private:
    /**
     * Helper to generate all subset sums for a sub-vector.
     * @param nums The subset of numbers to process.
     * @param results A vector to store pairs of {sum, mask}.
     * Mask is a bitmask representing which indices were picked.
     */
    void generateSubsets(const std::vector<long long>& nums,
                         std::vector<std::pair<long long, unsigned long long>>& results);
};