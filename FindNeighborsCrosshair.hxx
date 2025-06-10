#pragma once
#include "PointSheet.hxx"

namespace NeighborFinder {

    /**
     * @brief A functor to find the nearest x neighbors of a point in a
     * set of other points using the crosshair method.
     * 
     * The search area is defined with a crosshair. Instead of maintaining a whole 
     * grid of bins, we can just maintain 2 sorted lists of the points: one 
     * sorted by x-coordinate, and the other by y-coordinate. When searching 
     * for some nearest neighbors we can search outward from the coordinates 
     * of the point in question.
     * 
     * I expect this option is particularly useful when searching for all 
     * points within a certain distance of another point, instead of the 
     * nearest neighbors. It allows us to define the box to search in: if 
     * looking for all points within a distance of 15, there's no need to 
     * look at points with an x || y distance > 15
     */
    class FindNeighborsCrosshair {
        public:
        FindNeighborsCrosshair() = delete;
        FindNeighborsCrosshair(PointSheet sheet);

        // get the n neighbors
        std::vector<Point*> operator()(Point point, int numNeighbors);

        private:
        PointSheet m_sheet;
        std::vector<Point*> m_pointsX; // sheet sorted by x-coord
        static bool xCoordComp(Point* left, Point* right);
        std::vector<Point*> m_pointsY; // sheet sorted by y-coord
        static bool yCoordComp(Point* left, Point* right);
    };
}