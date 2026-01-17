#include "dp-solver.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

std::string DPSolver::getAlgorithmName() const {
    return "Dynamic Programming (Negative Support)";
}

long long DPSolver::solve(const std::vector<long long> &numbers, long long target) {
    // 1. Clear previous results (using the member variable from the base/header)
    solutionSubset.clear(); // Ensure this matches the name in your solver.h (solution_subset vs solutionSubset)

    long long n = numbers.size();

    // 2. Determine the range of possible sums
    // We need this to determine the offset and table size
    long long min_possible_sum = 0;
    long long max_possible_sum = 0;

    for (long long val : numbers) {
        if (val < 0) min_possible_sum += val;
        else max_possible_sum += val;
    }

    // "Offset" is what we add to a real sum to get its array index.
    // Example: If min sum is -50, offset is +50. Real sum -50 becomes index 0.
    long long offset = -min_possible_sum;
    long long range = max_possible_sum - min_possible_sum + 1;

    // Safety check: If the range is massive (e.g., billions), DP will crash memory.
    if (range > 200000000) { // arbitrary safety limit (~200MB)
        std::cerr << "Warning: Sum range is too large for DP table." << std::endl;
        return 0;
    }

    // 3. Initialize DP Table
    // dp[i][j] means: Using first 'i' items, is sum (j - offset) possible?
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(range, false));

    // Base Case: Sum 0 is always possible
    // The index for sum 0 is (0 + offset)
    dp[0][offset] = true;

    // 4. Fill the table
    for (long long i = 1; i <= n; ++i) {
        long long current_val = numbers[i - 1];

        for (long long j = 0; j < range; ++j) {
            // Option A: Exclude the current number
            bool possible = dp[i - 1][j];

            // Option B: Include the current number
            // We need to check the previous state.
            // Current index 'j' represents real sum S.
            // We need previous real sum (S - current_val).
            // Previous index = (j - offset - current_val) + offset
            //                = j - current_val
            long long prev_index = j - current_val;

            if (prev_index >= 0 && prev_index < range) {
                possible = possible || dp[i - 1][prev_index];
            }

            dp[i][j] = possible;
        }
    }

    // 5. Find the closest sum <= target
    // We want the largest index 'j' such that dp[n][j] is true AND (j - offset) <= target.
    // (j - offset) <= target  =>  j <= target + offset

    long long best_sum = LLONG_MIN; // Initialize to LLONG_MIN
    long long start_search_index = target + offset;

    // Clamp search index to the table bounds
    if (start_search_index >= range) start_search_index = range - 1;

    // If target is smaller than the smallest possible sum, we can't start search
    if (start_search_index < 0) {
        return best_sum; // Return failure (or handle as "no solution")
    }

    int found_index = -1;
    for (long long j = start_search_index; j >= 0; --j) {
        if (dp[n][j]) {
            best_sum = j - offset;
            found_index = j;
            break;
        }
    }

    if (found_index == -1) return best_sum; // No valid sum found

    // 6. Backtrack to find the subset
    long long current_index = found_index;

    for (long long i = n; i > 0; --i) {
        // Look at the cell directly above (dp[i-1][current_index]).
        // If it's true, it means we could form this sum WITHOUT the current item.
        if (dp[i - 1][current_index]) {
            continue; // Skip item
        }

        // If false, we MUST have used the current item.
        long long val = numbers[i - 1];
        solutionSubset.push_back(val);

        // Move our index back by the value of the item
        // prev_index = current_index - val
        current_index = current_index - val;
    }

    return best_sum;
}