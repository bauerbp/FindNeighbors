#pragma once
#include <cmath>
#include <vector>

namespace NeighborFinder {

using CoordinateType = double;

struct Point {

    /**
     * A simple 2D point implementation.
     */
    Point(CoordinateType x, CoordinateType y) : x(x), y(y) {}
    CoordinateType x;
    CoordinateType y;
    // neat: Don't have to define all of the comparison operators.
    // https://www.reddit.com/r/cpp/comments/11bae6w/avoid_the_code_smell_of_stdpair_and_stdtuple/
    /// Edit: The defaults are not useful. For comparison and equality, it will only check the variables
    /// in order of declaration until it has a result. So it always only checks `x`.
    /// https://en.cppreference.com/w/cpp/language/default_comparisons.html
    auto operator <=> (const Point& rhs) const = default;

    // thanks, pythagoras
    double distanceTo(const Point& other) const {
        double xDiff = this->x - other.x;
        double yDiff = this->y - other.y;
        return sqrt(pow(xDiff, 2) + pow(yDiff, 2));
    }
};

/**
 * Represents a set of 2D points
 */
typedef std::vector<Point*> PointSheet;

}