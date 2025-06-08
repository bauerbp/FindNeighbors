#pragma once
#include "PointSheet.hxx"

namespace NeighborFinder {

    struct Grid {
        // Generates a number of random points
        Grid(size_t pointCount);
        // Generates a Grid from an existing set of points
        Grid(PointSheet sheet);

        std::vector<Point*> getBinOfPoint(Point);

        std::vector<std::vector<Point*>> getBinsAdjacentToPoint(Point);

        private:
        void fillGrid(PointSheet);
        int getFlattenedBinIndexOfPoint(Point);
        bool isIndexValid(int);
        // This is a flat matrix of bins which have points in them.
        std::vector<std::vector<Point*>> m_grid;
        CoordinateType m_minX;
        CoordinateType m_maxX;
        CoordinateType m_minY;
        CoordinateType m_maxY;

        size_t m_binWidth;
        size_t m_binHeight;
        size_t m_gridDimensions;
    };

}