## Command-Line Usage

### Run the Subset Sum Solver
The main executable is `bin/subset_sum`. You can run it directly on any test file:

```sh
./bin/subset_sum <input_file> <method> [debug]
```

- `<input_file>`: Path to a test file (see `tests/` for examples)
- `<method>`: Algorithm to use (`dp`, `mitm`, or `sa`)
- `[debug]`: Any value enables verbose/debug output (optional)

#### Example:
```sh
./bin/subset_sum tests/high_n_100.in dp debug
```

#### Output:
- If debug is enabled, prints the closest or exact sum found, the subset used, and the sum of the subset.
- If the subset sum does not match the reported result, a warning is printed.

### Test Files
Test files are generated in the `tests/` directory using `make tests`. Each file contains:
- The number of elements
- The target sum
- The list of numbers

### Methods
- `dp`: Dynamic Programming
- `mitm`: Meet-in-the-Middle
- `sa`: Simulated Annealing

### Debug Output
Add any third argument to enable debug output and see the subset and sum details.

## Makefile Usage

### Build the Project
Compile all sources and produce the executable in `bin/`:
```sh
make build
```
or simply:
```sh
make
```
This is the default target.

### Install Dependencies
Set up the Python virtual environment and install all required system and Python packages:
```sh
make install
```

### Generate Test Files
Create a variety of test input files in the `tests/` directory:
```sh
make tests
```

### Clean Build Artifacts
Remove all compiled objects and binaries:
```sh
make clean
```

---

## Benchmarking and Plotting


### Test Classes
- **mitm_bench_***: Small N, stress for MITM (Meet-in-the-Middle). Shows where MITM is efficient.
- **dp_magnitude_***: Fixed N, increasing target magnitude. Shows DP's pseudo-polynomial behavior.
- **high_n_***: High N, moderate values. Compares DP and SA as N increases, shows where DP fails and SA survives.
- **hard_sa_*_sol**: Hard for SA, but with a guaranteed solution (target is sum of a random subset). Tests if SA can find the true solution in a large, tricky space.
- **hard_sa_*_nosol**: Hard for SA, target is set just above the max possible subset sum (sum of all positives), so no subset can reach it. Tests how close SA can get when the target is impossible.

### Benchmark Rules
- **bench_scaling**: Compares MITM and DP as N increases (scaling behavior).
- **bench_dp_magnitude**: Shows how DP's time grows with target magnitude.
- **bench_high_n_comparison**: Compares DP and SA for high N (where DP starts to fail).
- **bench_sa_stability**: Runs SA multiple times on the same input to show its variance (stability).
- **bench_hard_sa**: Runs SA on the hardest tests (both with and without solution) to see how it performs in the most challenging cases.
- **bench_all**: Runs all benchmarks in sequence.

---

## Notes

- All benchmark results are saved in the `bench_results/` directory.
- Plots are saved in the `plots/` directory.
- You can always run `make <target>` to execute any of the above rules.

---

## Quick Start

### 1. Clone the repository
```
git clone https://github.com/Mihnea240/aa-subset-sum.git
cd subset-sum
```

### 2. Build and install dependencies
The following command will build the project and automatically run the install script for dependencies:
```
make
```

The compiled binary will be in the `bin/` directory.
