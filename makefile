# Compiler and flags
CXX = clang++
CXXFLAGS = -g -O3 $(shell llvm-config --cxxflags)

# Source and target files
SRC = tokanize.cpp
TARGET = lingua.out

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean

