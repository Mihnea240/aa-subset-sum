#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "dp-solver.h"
#include "mitm-solver.h"
#include "sa-solver.h"

using namespace std;

void printUsage() {
	cout << "Usage: ./subset_sum <input_file> <method> <bebug?>\n";
	cout << "Methods: dp, mitm, sa\n";
	cout << "Set debug to any value to enable debug output.\n";
}

int main(int argc, char *argv[]) {

	if (argc < 3) {
		printUsage();
		return 1;
	}

	string filename = argv[1];
	string method = argv[2];
	int debug = argc >= 4;

	// Read input from file
	vector<long long> numbers;
	int count = 0;
	long long target;

	ifstream infile(filename);

	if(!infile.is_open()) {
		cerr << "Error opening file: " << filename << endl;
		return 1;
	}

	infile >> count;
	infile >> target;

	for (int i = 0; i < count; ++i) {
		long long num;
		infile >> num;
		numbers.push_back(num);
	}


	SubsetSumSolver* solver = nullptr;

	if (method == "dp") {
		solver = new DPSolver();
	} else if (method == "mitm") {
		solver = new MITMSolver();
	} else if (method == "sa") {
		solver = new SASolver();
	} else {
		cerr << "Unknown method: " << method << endl;
		printUsage();
		return 1;
	}

	long long result = solver->solve(numbers, target);
	auto subset = solver->getSolutionSubset();

	if(!debug) {
		return 0;
	}

	if (result != target) {
		cout << "Closest sum found: " << result << " (target was " << target << ")\n";
	} else {
		cout << "Exact sum found: " << result << "\n";
	}

	cout << "Subset used:\n";
	long long sum = 0;
	for (const auto &val : subset) {
		cout << val << " ";
		sum+= val;
	}

	cout << "\nSubset sum: " << sum << endl;

	if (sum != result) {
		cout << "Warning: Calculated subset sum " << sum << " does not match reported result " << result << endl;
		return 2;
	}

	return 0;
}
