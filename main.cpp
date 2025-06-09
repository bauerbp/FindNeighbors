#include <iostream>
#include <vector>
#include <string>

#include "FindNeighborsGrid.hxx"
#include "PointSheet.hxx"
#include "tests.hxx"

using namespace std;

int main()
{
    auto sheet1 = testSheet1();
    auto sheet2 = testSheet2();
    printSheet(sheet1);
    printSheet(sheet2);

    FindNeighborsGrid gridFind(sheet1);
    auto neighbors1 = gridFind(Point(5,5), 5);
    printSheet(neighbors1);
    
    auto neighbors2 = gridFind(Point(5,5), 6);
    printSheet(neighbors2);
}
