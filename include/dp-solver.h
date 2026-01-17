#pragma once

#include "solver.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class DPSolver : public SubsetSumSolver {
public:
	std::string getAlgorithmName() const override;
	long long solve(const std::vector<long long> &numbers, long long target) override;
};
