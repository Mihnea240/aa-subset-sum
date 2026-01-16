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

# Alias for build
build: all

# Linking: Combine all .o files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation: Convert each .cpp file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


bench_dp: 
	hyperfine --show-output --warmup 3 --export-json results_bench_dp.json \
		"./bin/subset_sum tests/small_pos.in dp" \
		"./bin/subset_sum tests/small_pos.in mitm" \
		"./bin/subset_sum tests/small_neg.in dp" \
		"./bin/subset_sum tests/small_neg.in mitm" \
		"./bin/subset_sum tests/target_zero.in dp" \
		"./bin/subset_sum tests/target_zero.in mitm"

# Cleanup
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all build install clean bench