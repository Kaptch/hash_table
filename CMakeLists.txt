cmake_minimum_required(VERSION 3.9)
project(hash_table)

set(CMAKE_CXX_STANDARD 17)

add_executable(hash_table main.cpp hash_table.h hash_table_utils.h)