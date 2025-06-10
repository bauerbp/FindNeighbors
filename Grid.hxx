#pragma once
#include <set>
#include "PointSheet.hxx"

namespace NeighborFinder {

    /**
     * @brief The grid class is used to track where points are.
     * 
     * The grid is a flattened matrix of bins superimposed on the 2D points.
     * Each bin is a vector of Point pointers.
     */
    struct Grid {
        // Generates a number of random points
        Grid(size_t pointCount);
        // Generates a Grid from an existing set of points
        Grid(PointSheet sheet);

        // Collects however many bins of points it needs to in order to have
        // at least the number of nearest points requested
        std::vector<Point*> getCombinedBinsToCheck(Point, int);

        // TODO: write a debug dump to make sure that the grid looks right

        private:
        void fillGrid(PointSheet);
        void dumpGrid();

        std::vector<Point*> getBinContents(int);
        std::vector<std::vector<Point*>> getBinsAdjacentToPoint(Point);
        std::set<int> getAdjacentBinIndices(int binIndex);
        int getFlattenedIndex(int x, int y);
        int getFlattenedBinIndexOfPoint(Point);
        bool isIndexValid(int);
        // This is a flat matrix of bins which have points in them.
        std::vector<std::vector<Point*>> m_grid;
        CoordinateType m_minX;
        CoordinateType m_maxX;
        CoordinateType m_minY;
        CoordinateType m_maxY;

        double m_binWidth;
        double m_binHeight;

        // How many bins across
        size_t m_gridDimensions;
    };

}