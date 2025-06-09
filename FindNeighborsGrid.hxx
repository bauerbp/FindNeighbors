#pragma once
#include "PointSheet.hxx"
#include "Grid.hxx"

namespace NeighborFinder {

    class FindNeighborsGrid {
        public:
        FindNeighborsGrid() = delete;
        FindNeighborsGrid(PointSheet sheet);

        // get the n neighbors
        std::vector<Point*> operator()(Point point, int numNeighbors);

        private:
        // grid
        Grid m_grid;
    };
}