#include <algorithm>
#include "FindNeighborsCrosshair.hxx"

#include "tests.hxx"

using namespace NeighborFinder;

FindNeighborsCrosshair::FindNeighborsCrosshair(PointSheet sheet) {
    // Create the sorted lists
    m_pointsX = sheet;
    std::sort(m_pointsX.begin(), m_pointsX.end(), xCoordComp);
    
    m_pointsY = sheet;
    std::sort(m_pointsY.begin(), m_pointsY.end(), yCoordComp);
}

bool FindNeighborsCrosshair::xCoordComp(Point* left, Point* right) {
    if (left->x == right->x)
        return left->y < right->y;
    return left->x < right->x;
}

bool FindNeighborsCrosshair::yCoordComp(Point* left, Point* right) {
    if (left->y == right->y)
        return left->x < right->x;
    return left->y < right->y;
}

std::vector<Point*> FindNeighborsCrosshair::operator()(Point point, int neighbors) {
    // Find coordinate in x-sorted list
    auto xIter = std::lower_bound(m_pointsX.begin(), m_pointsX.end(), &point, xCoordComp);

    // Find coordinate in y-sorted list
    auto yIter = std::lower_bound(m_pointsY.begin(), m_pointsY.end(), &point, yCoordComp);

    // start looking outward from the iterators.


    return {};
}