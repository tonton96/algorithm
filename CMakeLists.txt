cmake_minimum_required(VERSION 3.23)
project(algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(algorithm main.cpp alg/my_algorithm.cpp alg/my_algorithm.h hacker_rank.h)
