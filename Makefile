LIB_DIR = ./lib
SRC_DIR = ./src
TEST_DIR = ./test
BIN_DIR = ./bin

CXX = g++
CXXFLAGS = -std=c++11

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
		$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -c $(TEST_DIR)/test_main.cpp -o $(BIN_DIR)/test_main.o; \
	fi

.PHONY: tinystl_tests
tinystl_tests: allocator utils array list vector stack queue priority_queue hash_table hash_set hash_map tree tree_set tree_map bitset

allocator: $(TEST_DIR)/test_allocator.cpp $(SRC_DIR)/allocator.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_allocator.cpp -o $(BIN_DIR)/test_allocator.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_allocator.o -o $(BIN_DIR)/test_allocator

utils: $(TEST_DIR)/test_utils.cpp $(SRC_DIR)/utils.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_utils.cpp -o $(BIN_DIR)/test_utils.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_utils.o -o $(BIN_DIR)/test_utils

array: $(TEST_DIR)/test_array.cpp $(SRC_DIR)/array.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_array.cpp -o $(BIN_DIR)/test_array.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_array.o -o $(BIN_DIR)/test_array

list: $(TEST_DIR)/test_list.cpp $(SRC_DIR)/list.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_list.cpp -o $(BIN_DIR)/test_list.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_list.o -o $(BIN_DIR)/test_list

vector: $(TEST_DIR)/test_vector.cpp $(SRC_DIR)/vector.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_vector.cpp -o $(BIN_DIR)/test_vector.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_vector.o -o $(BIN_DIR)/test_vector

stack: $(TEST_DIR)/test_stack.cpp $(SRC_DIR)/stack.hpp $(SRC_DIR)/list.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_stack.cpp -o $(BIN_DIR)/test_stack.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_stack.o -o $(BIN_DIR)/test_stack

queue: $(TEST_DIR)/test_queue.cpp $(SRC_DIR)/queue.hpp $(SRC_DIR)/list.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_queue.cpp -o $(BIN_DIR)/test_queue.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_queue.o -o $(BIN_DIR)/test_queue

priority_queue: $(TEST_DIR)/test_priority_queue.cpp $(SRC_DIR)/priority_queue.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_priority_queue.cpp -o $(BIN_DIR)/test_priority_queue.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_priority_queue.o -o $(BIN_DIR)/test_priority_queue

hash_table: $(TEST_DIR)/test_hash_table.cpp $(SRC_DIR)/hash_table.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_hash_table.cpp -o $(BIN_DIR)/test_hash_table.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_hash_table.o -o $(BIN_DIR)/test_hash_table

hash_set: $(TEST_DIR)/test_hash_set.cpp $(SRC_DIR)/hash_set.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_hash_set.cpp -o $(BIN_DIR)/test_hash_set.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_hash_set.o -o $(BIN_DIR)/test_hash_set

hash_map: $(TEST_DIR)/test_hash_map.cpp $(SRC_DIR)/hash_map.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_hash_map.cpp -o $(BIN_DIR)/test_hash_map.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_hash_map.o -o $(BIN_DIR)/test_hash_map

tree: $(TEST_DIR)/test_tree.cpp $(SRC_DIR)/tree.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_tree.cpp -o $(BIN_DIR)/test_tree.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_tree.o -o $(BIN_DIR)/test_tree

tree_set: $(TEST_DIR)/test_tree_set.cpp $(SRC_DIR)/tree_set.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_tree_set.cpp -o $(BIN_DIR)/test_tree_set.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_tree_set.o -o $(BIN_DIR)/test_tree_set

tree_map: $(TEST_DIR)/test_tree_map.cpp $(SRC_DIR)/tree_map.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_tree_map.cpp -o $(BIN_DIR)/test_tree_map.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_tree_map.o -o $(BIN_DIR)/test_tree_map

bitset: $(TEST_DIR)/test_bitset.cpp $(SRC_DIR)/bitset.hpp
	$(CXX) $(CXXFLAGS) -I $(LIB_DIR) -I $(SRC_DIR) -c $(TEST_DIR)/test_bitset.cpp -o $(BIN_DIR)/test_bitset.o
	$(CXX) $(BIN_DIR)/test_main.o $(BIN_DIR)/test_bitset.o -o $(BIN_DIR)/test_bitset

# run all tests
.PHONY: test_all
test_all:
	@sh run_tests.sh

# run given test
.PHONY: test
test:
	@chmod +x $(BIN_DIR)/*
	@./$(BIN_DIR)/test_tree_map

.PHONY: clean
clean:
	@rm -rf $(BIN_DIR)
