set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_minimum_required(VERSION 4.0)

project(FindNeighbors VERSION 1.0)

add_executable(FindNeighbors main.cpp)

target_sources(FindNeighbors PRIVATE "FindNeighborsGrid.cxx" "Grid.cxx" "PointSheet.hxx")
