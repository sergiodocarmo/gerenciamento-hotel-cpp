CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -Iheader
BIN_DIR = bin
SRC_DIR = src
DATA_DIR = data

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES))

EXECUTABLE = $(BIN_DIR)/main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)

run:
	./$(EXECUTABLE)

.PHONY: all clean run
