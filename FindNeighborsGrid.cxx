#include <algorithm>
#include "FindNeighborsGrid.hxx"

using namespace NeighborFinder;

FindNeighborsGrid::FindNeighborsGrid(PointSheet sheet) : m_grid(sheet) {
  // N/a
}

std::vector<Point*> FindNeighborsGrid::operator()(Point point, int neighbors) {
    // Get points from current and nearby bins to check
    auto binPoints = m_grid.getCombinedBinsToCheck(point, neighbors);
    
    auto distanceComp = [&point](Point *left, Point *right) -> bool {
        return point.distanceTo(*left) < point.distanceTo(*right);
    };
    std::sort(binPoints.begin(), binPoints.end(), distanceComp);
    int numPoints = binPoints.size();
    neighbors = std::min(neighbors, numPoints);

    std::vector<Point*> nearestPoints(binPoints.begin(), binPoints.begin()+neighbors);
    return nearestPoints;
}
