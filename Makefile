# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Iinclude -I/opt/homebrew/include

# Source files and output binary
SRC = src/main.cpp src/item.cpp src/inventory.cpp src/commands.cpp
TARGET = bin/main

# Default rule to build executable
all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean rule to remove output binary
clean:
	rm -f $(TARGET)