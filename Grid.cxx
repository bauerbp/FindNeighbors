#include "Grid.hxx"
#include <cmath>
#include <cassert>
#include <iostream>
#include <set>

using namespace NeighborFinder;
/**
 * The Constructor for a Grid.
 * 
 * @param pointSheet A vector of 2D Point object pointers.
 */
Grid::Grid(PointSheet pointSheet) : m_minX(0),
                                    m_maxX(0),
                                    m_minY(0),
                                    m_maxY(0),
                                    m_binHeight(0),
                                    m_binWidth(0),
                                    m_gridDimensions(0) {
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

    // Just divide into 20 rows and 20 columns. Pretty arbitrary, and
    // I'm sure there are better ways. But for now...
    m_gridDimensions = 20;
    m_binWidth = xSpread / m_gridDimensions;
    m_binHeight = ySpread / m_gridDimensions;
    m_grid.resize(m_gridDimensions*m_gridDimensions);
    fillGrid(pointSheet);
}

/**
 * Populates the grid but placing the points in the appropriate
 * bins.
 * 
 * @param pointSheet A vector of 2D Point object pointers.
 */
void Grid::fillGrid(PointSheet points) {
    for (auto& point : points) {
        auto index = getFlattenedBinIndexOfPoint(*point);
        if(!isIndexValid(index)) {
            assert((void("fillGrid"), isIndexValid(index)));
        }
        m_grid[index].push_back(point);
    }
}

/**
 * Check if a bin index is valid
 */
bool Grid::isIndexValid(int index) {
    if (index < 0) {
        return false;
    }
    if (index >= m_gridDimensions*m_gridDimensions) {
        return false;
    }
    return true;
}

/**
 * Gives the vector of Point pointers in a bin.
 * 
 * @param binIndex The index of the bin you want the points of.
 */
std::vector<Point*> Grid::getBinContents(int binIndex) {
    assert((void("getBinOfPoint"), isIndexValid(binIndex)));
    return m_grid.at(binIndex);
}

/**
 * generic function to flatten index
 */
int Grid::getFlattenedIndex(int x, int y) {
    return x + y * m_gridDimensions;
}

/**
 * Figure out which bin a given point ought to be in.
 */
int Grid::getFlattenedBinIndexOfPoint(Point point) {
    // The bin's index
    auto indexX =
        std::floor((point.x - m_minX) / m_binWidth);
    auto indexY =
        std::floor((point.y - m_minY) / m_binHeight);

    if (indexX >= m_gridDimensions) {
        indexX = m_gridDimensions - 1;
    }
    if (indexY >= m_gridDimensions) {
        indexY = m_gridDimensions - 1;
    }

    // get the flattened index
    return getFlattenedIndex(indexX, indexY);
}

/**
 * Returns the set of bin indices which are adjacent (diagonals included) 
 * to the given bin.
 * 
 * @param centralBinIndex The index of the bin for which you want to find the
 * adjacent bin indices.
 */
std::set<int> Grid::getAdjacentBinIndices(int centralBinIndex) {
    std::set<int> outIndices;
    // Unflatten index
    int indexX = centralBinIndex % m_gridDimensions;
    int indexY = (centralBinIndex - indexX) / m_gridDimensions;

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

/**
 * @brief Returns the points that the nearest neighbors must be in.
 * 
 * This is an important method. If you give a point and request some number
 * of neighbors, it will continue gathering the points from bins near to
 * the bin of the input point until it has at least as many points as there
 * are neighbors requested; or until there are no more points to gather.
 * 
 * @param point The position the user wants to find the points nearest to. It
 * doesn't have to exist in the point sheet already.
 * @param neighbors The number of neighbors to find.
 */
std::vector<Point*> Grid::getCombinedBinsToCheck(Point point, int neighbors) {
    std::set<int> binIndices;
    auto pointBinIndex = getFlattenedBinIndexOfPoint(point);
    binIndices.insert(pointBinIndex); // accumulated bins
    std::vector<Point*> accumulatedPoints = getBinContents(pointBinIndex);

    // Keep gathering until we have a number to search which is at least the number of neighbors
    while (accumulatedPoints.size() < neighbors) {
        std::set<int> unsearchedBins;

        // Broaden our search, but don't bother with bins we've already looked in
        for(auto bins : binIndices) {
            auto newAdj = getAdjacentBinIndices(bins);
            for (auto adj : newAdj) {
                if (!binIndices.contains(adj)) {
                    unsearchedBins.insert(adj);
                }
            }
        }

        // We've gathered as many points as there are
        if (unsearchedBins.empty()) {
            break;
        }

        for (auto index : unsearchedBins) {
            auto newPoints = getBinContents(index);
            accumulatedPoints.insert(accumulatedPoints.begin(), newPoints.begin(), newPoints.end());
        }
        // These are now already accumulated
        binIndices.insert(unsearchedBins.begin(), unsearchedBins.end());
    }
    return accumulatedPoints;
}