#pragma once

#include "solver.h"
#include <vector>
#include <utility>

class MITMSolver : public SubsetSumSolver {
public:
	std::string getAlgorithmName() const override;
	long long solve(const std::vector<long long> &numbers, long long target) override;
	void generateSubsets(const std::vector<long long>& nums,
                                 std::vector<std::pair<long long, unsigned long long>>& results);
};