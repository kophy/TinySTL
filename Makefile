LIBS_DIR = ./3rd-party
SRCS_DIR = ./src
TEST_DIR = ./test
BINS_DIR = ./bin

CXX = g++
CXXFLAGS = -g -Wall -std=c++11

.PHONY: all
all: dir array

.PHONY: dir
dir:
	@-mkdir $(BINS_DIR)

array: $(TEST_DIR)/test_array.cpp $(SRCS_DIR)/array.hpp
	g++ -I $(LIBS_DIR) -I $(SRCS_DIR) $(TEST_DIR)/test_array.cpp -o $(BINS_DIR)/test_array

.PHONY: test
test:
	@chmod +x $(BINS_DIR)/*
	@./$(BINS_DIR)/test_array

.PHONY: clean
clean:
	@rm -rf $(BINS_DIR)
