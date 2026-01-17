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
