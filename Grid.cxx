#include "Grid.hxx"
#include <cmath>
#include <cassert>
#include <iostream>
#include <set>

using namespace NeighborFinder;

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
        if(!isIndexValid(index)) {
            assert((void("fillGrid"), isIndexValid(index)));
        }
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

std::vector<Point*> Grid::getBinContents(int binIndex) {
    assert((void("getBinOfPoint"), isIndexValid(binIndex)));
    return m_grid.at(binIndex);
}

// generic function to flatten index
int Grid::getFlattenedIndex(int x, int y) {
    return x + y * m_gridDimensions;
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

std::set<int> Grid::getAdjacentBinIndices(int centralBinIndex) {
    std::set<int> outIndices;
    // Unflatten index
    int indexX = centralBinIndex % m_gridDimensions;
    int indexY = centralBinIndex - indexX;

    // lil util to make sure we're not going out of bounds
    auto isOk = [&](int i) -> bool { 
        return i >= 0 && i < m_gridDimensions; 
    };

    // n compass direction
    if (isOk(indexX) && isOk(indexY-1)) {
        outIndices.insert(getFlattenedIndex(indexX, indexY-1));
    }
    // ne
    if (isOk(indexX+1) && isOk(indexY-1)) {
        outIndices.insert(getFlattenedIndex(indexX+1, indexY-1));
    }
    // e
    if (isOk(indexX+1) && isOk(indexY)) {
        outIndices.insert(getFlattenedIndex(indexX+1, indexY));
    }
    // se
    if (isOk(indexX+1) && isOk(indexY+1)) {
        outIndices.insert(getFlattenedIndex(indexX+1, indexY+1));
    }
    // s
    if (isOk(indexX) && isOk(indexY+1)) {
        outIndices.insert(getFlattenedIndex(indexX, indexY+1));
    }
    // sw
    if (isOk(indexX-1) && isOk(indexY+1)) {
        outIndices.insert(getFlattenedIndex(indexX-1, indexY+1));
    }
    // w
    if (isOk(indexX-1) && isOk(indexY)) {
        outIndices.insert(getFlattenedIndex(indexX-1, indexY));
    }
    // nw
    if (isOk(indexX-1) && isOk(indexY-1)) {
        outIndices.insert(getFlattenedIndex(indexX-1, indexY-1));
    }
    return outIndices;
}

std::vector<Point*> Grid::getCombinedBinsToCheck(Point point, int neighbors) {
    std::set<int> binIndices;
    auto pointBinIndex = getFlattenedBinIndexOfPoint(point);
    binIndices.insert(pointBinIndex);
    std::vector<Point*> accumulatedPoints = getBinContents(pointBinIndex);

    while (accumulatedPoints.size() < neighbors) {
        auto newAdj = getAdjacentBinIndices(pointBinIndex);
        for (auto index : newAdj) {
            auto newPoints = getBinContents(index);
            accumulatedPoints.insert(accumulatedPoints.begin(), newPoints.begin(), newPoints.end());
            
            binIndices.insert(newAdj.begin(), newAdj.end());
        }
    }
    return accumulatedPoints;
}