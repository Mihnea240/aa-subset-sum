#include "sa-solver.h"

std::string SASolver::getAlgorithmName() const {
	return "Simulated Annealing";
}

long long SASolver::solve(const std::vector<long long> &numbers, long long target) {
	this->solutionSubset.clear();

	// --- Tuning Parameters ---
	constexpr int MAX_ITERATIONS = 250000;
	constexpr double INITIAL_TEMP = 50000.0;
	constexpr double MIN_TEMP = 0.0001;
	constexpr double COOLING_RATE = 0.998;

	// --- Random Number Generator ---
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<double> dist_double(0.0, 1.0);
		
	int n = numbers.size();
	std::uniform_int_distribution<int> dist_index(0, n - 1);

	// --- 1. Initialization ---
	// State: 1 = included, 0 = excluded
	std::vector<int8_t> current_state(n);
	long long current_sum = 0;

	// Randomly fill initial state
	std::uniform_int_distribution<int> dist_bool(0, 1);
	for (int i = 0; i < n; ++i) {
		if (dist_bool(rng)) {
			current_state[i] = 1;
			current_sum += numbers[i];
		} else {
			current_state[i] = 0;
		}
	}

	// Track Best Solution found so far
	long long best_error = std::abs(current_sum - target);
	long long best_sum = current_sum;
	
	std::vector<int8_t> best_state = current_state; 
		
	double temperature = INITIAL_TEMP;

	// --- 2. Annealing Loop ---
	for (int iter = 0; iter < MAX_ITERATIONS; ++iter) {
			
		// Early exit if exact match found
		if (best_error == 0) {
			// Populate the solution vector before returning
			for (int i = 0; i < n; ++i) {
				if (best_state[i] == 1) {
					this->solutionSubset.push_back(numbers[i]);
				}
			}
			return target;
		}

		// Pick a random index to flip
		int idx = dist_index(rng);
			
		long long new_sum = current_sum;
			
		// Calculate new sum (O(1) update)
		if (current_state[idx] == 1) {
			new_sum -= numbers[idx];
		} else {
			new_sum += numbers[idx];
		}

		long long new_error = std::abs(new_sum - target);
		long long current_error = std::abs(current_sum - target);

		// --- Acceptance Logic ---
		bool accept = false;
			
		if (new_error < current_error) {
			accept = true; // Always accept improvements
		} else {
			// Metropolis criterion
			double p = std::exp((current_error - new_error) / temperature);
			if (dist_double(rng) < p) {
				accept = true;
			}
		}

		if (accept) {
			// Update Current State
			current_state[idx] = 1 - current_state[idx];
			current_sum = new_sum;

			// Update Global Best if this is the best we've seen
			if (new_error < best_error) {
				best_error = new_error;
				best_sum = current_sum;
				best_state = current_state;
			}
		}

		// --- Cooling ---
		if (temperature > MIN_TEMP) {
			temperature *= COOLING_RATE;
		}
	}

	// --- 3. Final Result Generation ---
	// If the loop finishes without an exact match, reconstruct the closest solution found
	for (int i = 0; i < n; ++i) {
		if (best_state[i] == 1) {
			this->solutionSubset.push_back(numbers[i]);
		}
	}

	return best_sum;
}
