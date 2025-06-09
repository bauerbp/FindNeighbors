#pragma once
#include "PointSheet.hxx"
#include <random>
#include <iostream>

using namespace NeighborFinder;
// test sheet with some hand-crafted, bespoke points
PointSheet testSheet1() {
    PointSheet sheet;
    sheet.push_back(new Point(5, 5)); // center
    sheet.push_back(new Point(5, 6)); // down
    sheet.push_back(new Point(5, 4)); // up
    sheet.push_back(new Point(4, 5)); // left
    sheet.push_back(new Point(6, 5)); // right
    sheet.push_back(new Point(6, 6)); // other
    return sheet;
}

// A bunch of random points
static PointSheet testSheet2() {
    PointSheet sheet;
    
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> numberMaker(0, 1000);
    for (auto i = 0; i < 10; ++i)
    {
        int x = numberMaker(e1);
        int y = numberMaker(e1);
        sheet.push_back(new Point(x, y));
    }
    return sheet;
}

static void printSheet(PointSheet sheet) {
    for (auto point : sheet) {
        std::cout << point->x << "," << point->y << "\n";
    }
    std::cout << sheet.size() << " points\n";
}