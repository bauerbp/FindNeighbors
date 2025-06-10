#include <algorithm>
#include "FindNeighborsCrosshair.hxx"

#include "tests.hxx"

using namespace NeighborFinder;

FindNeighborsCrosshair::FindNeighborsCrosshair(PointSheet sheet) {
    m_pointsX = sheet;
    std::sort(m_pointsX.begin(), m_pointsX.end(), [](Point* left, Point* right) -> bool 
                                                  {
                                                      return left->x < right->x;
                                                  }
    );
    
    m_pointsY = sheet;
    std::sort(m_pointsY.begin(), m_pointsY.end(), [](Point* left, Point* right) -> bool 
                                                  {
                                                      return left->y < right->y;
                                                  }
    );

    printSheet(m_pointsX);
    printSheet(m_pointsY);
}