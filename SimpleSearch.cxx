#include <algorithm>
#include "SimpleSearch.hxx"

using namespace NeighborFinder;

PointSheet NeighborFinder::SimpleSearch(PointSheet sheet, Point point, int neighbors) {
    // sort all points by distance to the point
    std::sort(sheet.begin(), sheet.end(),
        [&point](Point* left, Point* right) {
            return point.distanceTo(*left) < point.distanceTo(*right);
        }
    );

    neighbors = sheet.size() >= neighbors ? neighbors : sheet.size();
    // return the first n elements
    return std::vector<Point*>(sheet.begin(), sheet.begin()+neighbors);
}