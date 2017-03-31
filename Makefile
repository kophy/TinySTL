LIB_DIR = ./3rd-party
SRC_DIR = ./src
TEST_DIR = ./test
BIN_DIR = ./bin

CXX = g++
CXXFLAGS = -std=c++0x

.PHONY: all
all: dir array

.PHONY: dir
dir:
	@-mkdir $(BIN_DIR)

array: $(TEST_DIR)/test_array.cpp $(SRC_DIR)/array.hpp
	g++ $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) $(TEST_DIR)/test_array.cpp -o $(BIN_DIR)/test_array

.PHONY: test
test:
	@chmod +x $(BIN_DIR)/*
	@echo "testing array..."
	@./$(BIN_DIR)/test_array

.PHONY: clean
clean:
	@rm -rf $(BIN_DIR)
