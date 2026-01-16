#include "dp-solver.h"
#include <iostream>
#include <algorithm>

std::string DPSolver::getAlgorithmName() const {
    return "Dynamic Programming";
}

long long DPSolver::solve(const std::vector<long long> &numbers, long long target) {
    // 1. Clear previous results
    solutionSubset.clear();

    // Safety check: DP with target < 0 is invalid here
    if (target < 0) return 0;

    long long n = numbers.size();

    // 2. Initialize DP Table
    // dp[i][j] means: Can we sum to 'j' using the first 'i' numbers?
    // WARNING: This consumes O(n * target) memory.
    // Large targets (>10^8) will cause Bad Alloc/Segmentation Faults.
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));

    // Base case: Sum of 0 is always possible
    for (long long i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }

    // 3. Fill the table
    for (long long i = 1; i <= n; ++i) {
        long long current_val = numbers[i - 1];
        for (long long j = 1; j <= target; ++j) {
            if (current_val > j) {
                // Too big to include
                dp[i][j] = dp[i - 1][j];
            } else {
                // Exclude OR Include
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - current_val];
            }
        }
    }

    // 4. Find the closest sum <= target
    // We scan the last row (dp[n]) backwards from 'target'
    long long best_sum = 0;
    for (long long j = target; j >= 0; --j) {
        if (dp[n][j]) {
            best_sum = j;
            break;
        }
    }

    // 5. Backtrack to find the subset
    // We start from dp[n][best_sum] and walk back up
    long long current_sum = best_sum;
    for (long long i = n; i > 0 && current_sum > 0; --i) {
        // Check if the sum was possible WITHOUT including numbers[i-1]
        // If dp[i-1][current_sum] is true, it means we didn't need this item.
        if (dp[i - 1][current_sum]) {
            continue;
        }

        // If not, we MUST have used this item
        long long val = numbers[i - 1];
        solutionSubset.push_back(val);
        current_sum -= val;
    }

    return best_sum;
}