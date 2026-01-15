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

# Default rule: Build the final binary
all: setup $(TARGET)

# Create necessary directories
setup:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@bash scripts/install.sh

# Linking: Combine all .o files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation: Convert each .cpp file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Cleanup
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all setup clean bench