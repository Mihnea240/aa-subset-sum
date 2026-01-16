#include <iostream>
#include <vector>

#include "dp-solver.h"
#include "mitm-solver.h"
#include "sa-solver.h"

using namespace std;

int main() {
    DPSolver dpSolver;

    vector<long long> nums = {3, 34, 4, 12, 5, 2};
    long long target = 9;
    long long result = dpSolver.solve(nums, target);

    for (long long num : dpSolver.getSolutionSubset()) {
        cout << num << " ";
    }
    cout << "\nClosest sum to target " << target << " is: " << result<< "\n";
    return 0;
}