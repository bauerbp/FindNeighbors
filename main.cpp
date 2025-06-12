#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

#include "FindNeighborsCrosshair.hxx"
#include "FindNeighborsGrid.hxx"
#include "PointSheet.hxx"
#include "SimpleSearch.hxx"
#include "tests.hxx"
#include "Timer.hxx"

using namespace std;

int main()
{
    // auto sheet1 = testSheet1();
    // printSheet(sheet1);

    for(int ii = 5; ii < 6; ii++) {
        auto testSheet = genSheet(ii);

        auto firstPoint = testSheet.at(0);
        int numToFind = std::ceil(ii*.1);

        // Grid
        FindNeighborsGrid gridFind(testSheet);
        auto timerGrid = TickTock();
        timerGrid.tick();
        auto neighborsGrid = gridFind(*firstPoint, numToFind);
        auto gridMS = timerGrid.tock();

        // FindNeighborsCrosshair crossFind(sheet2);
        // auto neighborsCross = crossFind(Point(5, 5), 5);

        // Simple
        auto timerSimple = TickTock();
        timerSimple.tick();
        auto neighborsSimple = SimpleSearch(testSheet, *firstPoint, numToFind);
        auto simpleMS = timerSimple.tock();

        assert(neighborsSimple == neighborsGrid);
        std::cout << "Grid: " << gridMS << "\n";
        std::cout << "Simple: " << simpleMS << "\n";
        // TODO: print to file for plotting
    }
}
