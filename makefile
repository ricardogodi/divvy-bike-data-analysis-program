# Makefile for Divvy Bike Data Analysis Program

# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Target executable name
TARGET = divvy_analysis

# Source files
SRC = main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Build the program
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to clean files
clean:
	rm -f $(TARGET) $(OBJ)

# Rule to create object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<