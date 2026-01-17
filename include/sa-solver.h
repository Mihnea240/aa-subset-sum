#pragma once

#include "solver.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>
#include <ctime>
#include <chrono>

class SASolver: public SubsetSumSolver{
public:
	std::string getAlgorithmName() const override;
	long long solve(const std::vector<long long> &numbers, long long target) override;
};
