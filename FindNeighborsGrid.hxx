#pragma once
#include "PointSheet.hxx"
#include "Grid.hxx"

namespace NeighborFinder {

    /**
     * @brief A functor to find the nearest x neighbors of a point in a
     * set of other points using the grid method.
     * 
     * A grid of bins is used. Each bin holds its points. This gives us a way
     * to reduce where we are searching. If we want the nearest 10 points to 
     * point x we first search the point's bin. If we need more points we 
     * search all adjacent bins. If still more are needed, we again look to 
     * the next layer of bins, etc.
     */
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