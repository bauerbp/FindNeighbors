#pragma once
#include "PointSheet.hxx"

namespace NeighborFinder {

    class FindNeighborsCrosshair {

        FindNeighborsCrosshair() = delete;
        FindNeighborsCrosshair(PointSheet sheet);

        // get the n neighbors
        std::vector<Point> operator()(int numNeighbors);

        private:
        PointSheet m_sheet;
    };
}