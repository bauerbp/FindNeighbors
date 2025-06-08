#pragma once
#include "PointSheet.hxx"
#include "Grid.hxx"

namespace NeighborFinder {

    class FindNeighborsGrid {

        FindNeighborsGrid() = delete;
        FindNeighborsGrid(PointSheet sheet);

        // get the n neighbors
        std::vector<Point> operator()(int numNeighbors);

        private:
        // grid
        Grid m_grid;
    };
}