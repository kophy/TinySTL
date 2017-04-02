#!/usr/bin/env sh

BIN_DIR="bin"
chmod +x $BIN_DIR/*

echo "testing utils..."
./$BIN_DIR/test_utils

echo "testing array..."
./$BIN_DIR/test_array

echo "testing list..."
./$BIN_DIR/test_list

echo "testing vector..."
./$BIN_DIR/test_vector

echo "testing stack..."
./$BIN_DIR/test_stack

echo "testing queue..."
./$BIN_DIR/test_queue