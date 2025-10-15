# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Iinclude -I/opt/homebrew/opt/sfml/include

# Linker flags using Homebrew SFML
LDFLAGS = -L/opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,/opt/homebrew/opt/sfml/lib

# Source files and output binary
SRC = src/main.cpp
TARGET = bin/main

# Default rule to build executable
all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean rule to remove output binary
clean:
	rm -f $(TARGET)