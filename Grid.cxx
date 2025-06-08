#include "Grid.hxx"
#include <cmath>
#include <cassert>

using namespace NeighborFinder;

// Adapted from other project
Grid::Grid(PointSheet pointSheet) {
    // Find the bounds of the sheet
    for(auto& point : pointSheet) {
        m_minX = std::min(point->x, m_minX);
        m_minY = std::min(point->y, m_minY);
        m_maxX = std::max(point->x, m_maxX);
        m_maxY = std::max(point->y, m_maxY);
    }
    
    // Calculate Grid dimensions
    const CoordinateType xSpread = m_maxX - m_minX;
    const CoordinateType ySpread = m_maxY - m_minY;

    // Just divide into 20 rows and columns. Pretty arbitrary, and
    // I'm sure there are better ways. But for now...
    int gridDimension = 20;
    m_binWidth = static_cast<std::size_t>(
                  std::floor(xSpread / gridDimension)) +
               1;
    m_binHeight = static_cast<std::size_t>(
                   std::floor(ySpread / gridDimension)) +
               1;
    m_grid.resize(gridDimension*gridDimension);
    fillGrid(pointSheet);
}

void Grid::fillGrid(PointSheet points) {
    for (auto& point : points) {
        auto index = getFlattenedBinIndexOfPoint(*point);
        assert((void("fillGrid"), isIndexValid(index)));
        m_grid[index].push_back(point);
    }
}

bool Grid::isIndexValid(int index) {
    if (index < 0) {
        return false;
    }
    if (index >= m_gridDimensions) {
        return false;
    }
    return true;
}

std::vector<Point*> Grid::getBinOfPoint(Point point) {
    auto index = getFlattenedBinIndexOfPoint(point);
    assert((void("getBinOfPoint"), isIndexValid(index)));
    return m_grid.at(getFlattenedBinIndexOfPoint(point));
}

int Grid::getFlattenedBinIndexOfPoint(Point point) {
    // The bin's index
    auto indexX =
        std::floor((point.x - m_minX) / m_binWidth);
    auto indexY =
        std::floor((point.y - m_minY) / m_binHeight);

    // get the flattened index
    return indexX + indexY * m_gridDimensions;
}
