// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <numeric>
// #include <random>
// #include <algorithm>
// #include <ctime>
// #include <chrono>
// #include "include/sa-solver.h"

// class SubsetSumSolver : public SASubsetSumSolver {
// private:
//     double initial_temp;
//     double cooling_rate;
//     double min_temp;
//     int max_iterations;
//     std::mt19937 rng;

//     inline int getRandomInt(int min, int max) {
//         std::uniform_int_distribution<int> dist(min, max);
//         return dist(rng);
//     }

//     inline double getRandomDouble() {
//         std::uniform_real_distribution<double> dist(0.0, 1.0);
//         return dist(rng);
//     }

// public:
//     SubsetSumSolver(int max_iter = 25000000, double start_temp = 500000.0, double cool_rate = 0.9999998)
//         : max_iterations(max_iter), initial_temp(start_temp), cooling_rate(cool_rate), min_temp(0.00001) {
//         rng.seed(std::random_device{}());
//     }

//     long long solve(const std::vector<long long> &numbers, long long target) override {
//         int n = numbers.size();

//         std::vector<int8_t> current_state(n);
//         long long current_sum = 0;

//         // Random Initialization
//         for (int i = 0; i < n; ++i) {
//             if (getRandomInt(0, 1)) {
//                 current_state[i] = 1;
//                 current_sum += numbers[i];
//             } else {
//                 current_state[i] = 0;
//             }
//         }

//         long long best_error = std::abs(current_sum - target);
//         long long best_sum = current_sum;

//         double temperature = initial_temp;

//         for (int iter = 0; iter < max_iterations; ++iter) {
//             // Early exit if exact match found
//             if (best_error == 0) return target;

//             // Neighbor selection
//             int idx = getRandomInt(0, n - 1);
//             long long new_sum = current_sum;

//             // Flip logic
//             if (current_state[idx] == 1) {
//                 new_sum -= numbers[idx];
//             } else {
//                 new_sum += numbers[idx];
//             }

//             long long new_error = std::abs(new_sum - target);
//             long long current_error = std::abs(current_sum - target);

//             // Acceptance Logic
//             bool accept = false;
//             if (new_error < current_error) {
//                 accept = true;
//             } else {
//                 double p = std::exp((current_error - new_error) / temperature);
//                 if (getRandomDouble() < p) {
//                     accept = true;
//                 }
//             }

//             if (accept) {
//                 current_state[idx] = 1 - current_state[idx];
//                 current_sum = new_sum;

//                 if (new_error < best_error) {
//                     best_error = new_error;
//                     best_sum = current_sum;
//                 }
//             }

//             // Cooling
//             if (temperature > min_temp) {
//                 temperature *= cooling_rate;
//             }
//         }
//         return best_sum;
//     }
// };
