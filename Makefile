LIB_DIR = ./3rd-party
SRC_DIR = ./src
TEST_DIR = ./test
BIN_DIR = ./bin

CXX = g++
CXXFLAGS = -std=c++0x

.PHONY: all
all: dir catch tinystl_tests

# create directory for executable files
.PHONY: dir
dir:
	@-mkdir $(BIN_DIR)

# avoid repeated compileing of catch.hpp
.PHONY: catch
catch:
	@if [ ! -f $(BIN_DIR)/test_main.o ]; then \
		g++ $(CXXFLAGS) -I $(LIB_DIR) -c $(TEST_DIR)/test_main.cpp -o $(BIN_DIR)/test_main.o; \
	fi

.PHONY: tinystl_tests
tinystl_tests: array list stack queue

array: $(TEST_DIR)/test_array.cpp $(SRC_DIR)/array.hpp
	g++ $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_array.cpp -o $(BIN_DIR)/test_array.o
	g++ $(BIN_DIR)/test_main.o $(BIN_DIR)/test_array.o -o $(BIN_DIR)/test_array

list: $(TEST_DIR)/test_list.cpp $(SRC_DIR)/list.hpp
	g++ $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_list.cpp -o $(BIN_DIR)/test_list.o
	g++ $(BIN_DIR)/test_main.o $(BIN_DIR)/test_list.o -o $(BIN_DIR)/test_list

stack: $(TEST_DIR)/test_stack.cpp $(SRC_DIR)/stack.hpp $(SRC_DIR)/list.hpp
	g++ $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_stack.cpp -o $(BIN_DIR)/test_stack.o
	g++ $(BIN_DIR)/test_main.o $(BIN_DIR)/test_stack.o -o $(BIN_DIR)/test_stack

queue: $(TEST_DIR)/test_queue.cpp $(SRC_DIR)/queue.hpp $(SRC_DIR)/list.hpp
	g++ $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_queue.cpp -o $(BIN_DIR)/test_queue.o
	g++ $(BIN_DIR)/test_main.o $(BIN_DIR)/test_queue.o -o $(BIN_DIR)/test_queue

# run all tests
.PHONY: test_all
test_all:
	@chmod +x $(BIN_DIR)/*
	@echo "testing array..."
	@./$(BIN_DIR)/test_array
	@echo "testing list..."
	@./$(BIN_DIR)/test_list
	@echo "testing stack..."
	@./$(BIN_DIR)/test_stack
	@echo "testing queue..."
	@./$(BIN_DIR)/test_queue

# run given test
.PHONY: test
test:
	@chmod +x $(BIN_DIR)/*
	@./$(BIN_DIR)/test_queue

.PHONY: clean
clean:
	@rm -rf $(BIN_DIR)
