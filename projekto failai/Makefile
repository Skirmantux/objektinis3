# Compiler
CC := g++

# Compiler flags
CFLAGS := -std=c++20 -O3

# Source directory
SRC_DIR := src

# Header files
HEADERS := $(wildcard $(SRC_DIR)/*.h)

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRCS))

# Executable name
EXEC := v3.0.exe

# Default target
all: $(EXEC)

# Rule to compile .cpp files to .o files
%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link .o files to executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	del $(OBJS)

# Clean target
clean:
	del $(OBJS) $(EXEC)
