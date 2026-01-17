#include "mitm-solver.h"
#include <algorithm>
#include <cmath>

std::string MITMSolver::getAlgorithmName() const {
    return "Meet-in-the-Middle";
}

void MITMSolver::generateSubsets(const std::vector<long long>& nums,
                                 std::vector<std::pair<long long, unsigned long long>>& results) {
    int n = nums.size();
    int total_subsets = 1 << n; // 2^n

    results.reserve(total_subsets);

    for (int mask = 0; mask < total_subsets; ++mask) {
        long long current_sum = 0;
        for (int i = 0; i < n; ++i) {
            // Check if the i-th bit is set
            if (mask & (1 << i)) {
                current_sum += nums[i];
            }
        }
        results.push_back({current_sum, (unsigned long long)mask});
    }
}

long long MITMSolver::solve(const std::vector<long long>& numbers, long long target) {
    // 1. Clear previous results
    solutionSubset.clear();

    int n = numbers.size();
    if (n == 0) return 0;

    // 2. Split data into two halves
    int mid = n / 2;
    std::vector<long long> left_part(numbers.begin(), numbers.begin() + mid);
    std::vector<long long> right_part(numbers.begin() + mid, numbers.end());

    // 3. Generate all subset sums for both halves
    std::vector<std::pair<long long, unsigned long long>> left_sums;
    std::vector<std::pair<long long, unsigned long long>> right_sums;

    generateSubsets(left_part, left_sums);
    generateSubsets(right_part, right_sums);

    // 4. Sort the left side for binary search
    std::sort(left_sums.begin(), left_sums.end());

    // 5. Iterate through Right sums and match with Left
    long long best_sum = 0;
    unsigned long long best_left_mask = 0;
    unsigned long long best_right_mask = 0;


    for (const auto& r_pair : right_sums) {
        long long r_sum = r_pair.first;
        unsigned long long r_mask = r_pair.second;

        if (r_sum > target) continue;

        // We need: l_sum + r_sum <= target
        // So: l_sum <= target - r_sum
        long long remainder = target - r_sum;

        // Binary search (upper_bound) to find the first element > remainder
        auto it = std::upper_bound(left_sums.begin(), left_sums.end(),
                                   std::make_pair(remainder, (unsigned long long)-1));
        if (it != left_sums.begin()) {
            it--;

            long long current_total = r_sum + it->first;

            if (current_total > best_sum) {
                best_sum = current_total;
                best_left_mask = it->second;
                best_right_mask = r_mask;
            }
        }
    }

    // 6. Reconstruction: Decode the bitmasks back into the `solutionSubset` vector

    // Decode Left Half (Indices 0 to mid-1)
    for (int i = 0; i < mid; ++i) {
        if (best_left_mask & (1ULL << i)) {
            solutionSubset.push_back(left_part[i]);
        }
    }

    // Decode Right Half (Indices mid to n-1)
    for (int i = 0; i < (int)right_part.size(); ++i) {
        if (best_right_mask & (1ULL << i)) {
            solutionSubset.push_back(right_part[i]);
        }
    }

    return best_sum;
}