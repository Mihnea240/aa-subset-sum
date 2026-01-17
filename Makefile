# --- Compiler Settings ---
CXX      := g++
CXXFLAGS := -O3 -Wall -std=c++17 -Iinclude
# -Iinclude tells the compiler to look in the include/ folder for .h files

# --- Folders ---
SRC_DIR := src
INC_DIR := include
BIN_DIR := bin
OBJ_DIR := obj

# --- Files ---
# Finds all .cpp files in src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Converts src/*.cpp to obj/*.o
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET := $(BIN_DIR)/subset_sum

# --- Rules ---


# Install/setup: create directories and install requirements (run once)
install:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@bash scripts/install.sh

# Default rule: Build the final binary (no setup/install)
all: $(TARGET)

#Alias for build
build: all

# Linking: Combine all .o files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation: Convert each .cpp file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tests:
	@mkdir -p tests
	python3 scripts/test_generator.py

# 1. SCALING PLOT: How N impacts time (Logarithmic scale)
REPORT_DIR := plots
BENCH_DIR := bench_results

bench_scaling:
	hyperfine -L N 20,22,24,26,28,30,32,34,36,38 -N\
		--export-json $(BENCH_DIR)/mitm.json \
		"./bin/subset_sum tests/mitm_bench_{N}.in mitm"

	hyperfine -L N 20,22,24,26,28,30,32,34,36,38 -N\
		--export-json $(BENCH_DIR)/dp.json \
		"./bin/subset_sum tests/mitm_bench_{N}.in dp"

	python3 scripts/plot_parametrized.py\
		--log-time \
		--titles "MITM, DP" \
		-o $(REPORT_DIR)/scaling_dp_vs_mitm.png \
		$(BENCH_DIR)/mitm.json $(BENCH_DIR)/dp.json


bench_dp_magnitude:
	hyperfine -L mag 10,100,1000,10000,100000,1000000 \
		--export-json $(BENCH_DIR)/dp_mag.json \
		"./bin/subset_sum tests/dp_magnitude_{mag}.in dp"
	python3 scripts/plot_parametrized.py \
		--log-time \
		--log-x \
		--title "DP Time vs Magnitude of Numbers" \
		-o $(REPORT_DIR)/dp_magnitude_impact.png \
		$(BENCH_DIR)/dp_mag.json

bench_high_n_comparison:
    # Comparație DP vs SA pe scara 100-1000
	hyperfine -L n 100,200,400,600,800,1000 \
        --export-json $(BENCH_DIR)/high_n.json \
        "./bin/subset_sum tests/high_n_{n}.in dp" \
        "./bin/subset_sum tests/high_n_{n}.in sa"
	python3 scripts/plot_parametrized.py \
        --log-time --titles "DP, SA" \
        -o $(REPORT_DIR)/high_n_efficiency.png \
        $(BENCH_DIR)/high_n.json

bench_sa_stability:
	# Runs the same test 50 times to see the variance in SA performance
	hyperfine --runs 50 --export-json $(BENCH_DIR)/sa_stability.json \
		"./bin/subset_sum tests/high_n_500.in sa" \
		"./bin/subset_sum tests/high_n_500.in dp"
	# plot_whisker is the best for showing "Stability" (variance)
	python3 scripts/plot_whisker.py \
		-o $(REPORT_DIR)/sa_stability_whisker.png \
		$(BENCH_DIR)/sa_stability.json

# Cleanup
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all build install clean bench tests