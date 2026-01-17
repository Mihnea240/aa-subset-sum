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

### 1. Scaling Plot (`bench_scaling`)
Benchmarks both the DP and MITM algorithms on increasing input sizes and plots their performance:
```sh
make bench_scaling
```
- Output: `plots/scaling_dp_vs_mitm.png`

### 2. DP Magnitude Impact (`bench_dp_magnitude`)
Benchmarks the DP algorithm with increasing number magnitudes:
```sh
make bench_dp_magnitude
```
- Output: `plots/dp_magnitude_impact.png`

### 3. MITM Magnitude Impact (`bench_mitm_magnitude`)
Benchmarks the MITM algorithm with increasing input sizes:
```sh
make bench_mitm_magnitude
```
- Output: `plots/mitm_magnitude_impact.png`

### 4. Simulated Annealing Stability (`bench_sa_stability`)
Runs the Simulated Annealing and DP algorithms multiple times to compare their stability:
```sh
make bench_sa_stability
```
- Output: `plots/sa_stability_whisker.png`

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
