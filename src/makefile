# Compiler Variables
CXX = g++
CXXFLAGS = -Wall -std=c++17 -lncurses 
LDFLAGS = -lncurses
TARGET = main
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compiling the source file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
