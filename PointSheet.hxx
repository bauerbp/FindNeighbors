#pragma once
#include <cmath>
#include <vector>

namespace NeighborFinder {

using CoordinateType = double;

struct Point {
    Point(CoordinateType x, CoordinateType y) : x(x), y(y) {}
    CoordinateType x;
    CoordinateType y;
    // neat: Don't have to define all of the comparison operators.
    // https://www.reddit.com/r/cpp/comments/11bae6w/avoid_the_code_smell_of_stdpair_and_stdtuple/
    auto operator <=> (const Point& rhs) const = default;

    // thanks, pythagoras
    double distanceTo(const Point& other) {
        double xDiff = this->x - other.x;
        double yDiff = this->y = other.y;
        return sqrt(pow(xDiff, 2) + pow(yDiff, 2));
    }
};

/**
 * @brief Represents a set of 2D points
 */
typedef std::vector<Point*> PointSheet;

}