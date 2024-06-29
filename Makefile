# Define directories
SRC_DIR = src
BUILD_DIR = build

# Define compiler and flags
GCC = g++
GCC_FLAGS = -Wall -Wextra -std=c++11 -I$(SRC_DIR) -fPIC
LIB_FLAGS = $(GCC_FLAGS) -fPIC
LD_FLAGS = -shared

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# List of object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(SRCS))

# List of shared library files
SHARED_LIBS = $(patsubst $(SRC_DIR)/%.o, $(SRC_DIR)/%.so, $(OBJS))

# List of symlinks
SYMLINKS = $(patsubst $(SRC_DIR)/%.so, $(SRC_DIR)/lib%.so, $(SHARED_LIBS))

# Default target
libs: $(OBJS) $(SHARED_LIBS) $(SYMLINKS)

test:
	echo $(shell pwd)

# Rule to create symlinks
$(SRC_DIR)/lib%.so: $(SRC_DIR)/%.so
	ln -sf $(notdir $<) $@

# Rule to build shared libraries
$(SRC_DIR)/%.so: $(SRC_DIR)/%.o
	$(GCC) $(LD_FLAGS) -o $@ $<

# Rule to build object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp | $(SRC_DIR)
	$(GCC) $(LIB_FLAGS) -c $< -o $@

# Create include directory if it doesn't exist
$(SRC_DIR):
	mkdir -p $(SRC_DIR)

# Clean up build artifacts
clean:
	rm -f $(SRC_DIR)/*.o $(SRC_DIR)/*.so $(SRC_DIR)/lib*.so

# Phony targets
.PHONY: all clean
