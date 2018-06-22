/**
 * @file      map_to_graph.hpp
 * @brief     Class for the conversion of a boolean/binary matrix to a graph.
 * @author    Nick Swaerdens
 * @license   See LICENSE
 */

#ifndef MAP_TO_GRAPH_HPP
#define MAP_TO_GRAPH_HPP

#include "Pathfinding_mock/pathfinding.hpp"
#include "wrap-hwlib.hpp"
#include <array>

namespace Mapping {

template <typename T>
class mapToGraphConverter {
  private:
    // Temporary, edges can later be used to decide directions.
    enum class Direction { UP, RIGHT, DOWN, LEFT };
    Direction dir;
    Direction oppDir;

    Pathfinding::pathfindingWrap &pf;
    uint8_t nodeIndex;

    // Logic for traversing the grid.
    void moveGridPos(const bool &top, const bool &right, const bool &bottom, const bool &left) {
        if (top && oppDir != Direction::UP) {
            dir = Direction::UP;
            oppDir = Direction::DOWN;
        } else if (right && oppDir != Direction::RIGHT) {
            dir = Direction::RIGHT;
            oppDir = Direction::LEFT;
        } else if (bottom && oppDir != Direction::DOWN) {
            dir = Direction::DOWN;
            oppDir = Direction::UP;
        } else if (left && oppDir != Direction::LEFT) {
            dir = Direction::LEFT;
            oppDir = Direction::RIGHT;
        }
    }

    // Check pixel connectivity.
    uint8_t checkPixelConnectivity(const bool &top, const bool &right, const bool &bottom, const bool &left) {
        uint8_t edges = 0;
        if (top) {
            ++edges;
        }
        if (right) {
            ++edges;
        }
        if (bottom) {
            ++edges;
        }
        if (left) {
            ++edges;
        }

        moveGridPos(top, right, bottom, left);

        // Order of if statements should be optimized.
        if (edges == 1) { // End
            hwlib::cout << "o";
            ++nodeIndex;
        } else if (edges == 2) { // Corner or line
            if (top & bottom) {  // Vertical line
                hwlib::cout << "|";
            } else if (right & left) { // Horizontal line
                hwlib::cout << "-";
            } else { // Corner
                hwlib::cout << "o";
                ++nodeIndex;
            }
        } else if (edges == 3) { // Branch
            hwlib::cout << "o";
            ++nodeIndex;
        } else if (edges == 4) { // Intersection
            hwlib::cout << "o";
            ++nodeIndex;
        } else {
            hwlib::cout << "x";
        } // Alone

        return edges;
    }

  public:
    mapToGraphConverter(Pathfinding::pathfindingWrap &pf) : pf{pf}, nodeIndex{0} {
    }

    mapToGraphConverter(T &grid, Pathfinding::pathfindingWrap &pf, const uint8_t &startY, const uint8_t &startX)
        : pf{pf}, nodeIndex{0} {
        convert(grid, startY, startX);
    }

    // Only works for boolean matrices for now. Should be made compatible with binary matrices at a later date.
    Pathfinding::Graph convert(T &grid, const uint8_t &startY, const uint8_t &startX) {
        uint8_t colLen = grid.size();
        uint8_t rowLen = grid[0].size();

        uint8_t numEdges = 0;

        // Turn grid[startY][startX] into a node before conversion.

        for (uint8_t y = startY; y < colLen;) {
            for (uint8_t x = startX; x < rowLen;) {
                // If not on the boundaries.
                if (((y > 0) & (x > 0)) && ((y < (colLen - 1)) & (x < (rowLen - 1)))) {
                    numEdges = checkPixelConnectivity(grid[y - 1][x], grid[y][x + 1], grid[y + 1][x], grid[y][x - 1]);
                } else if (y == 0) { // Horizontal top boundary.
                    if (x == 0) {    // Top left corner.
                        numEdges = checkPixelConnectivity(0, grid[y][x + 1], grid[y + 1][x], 0);
                    } else if (x == (rowLen - 1)) { // Top right corner.
                        numEdges = checkPixelConnectivity(0, 0, grid[y + 1][x], grid[y][x - 1]);
                    } else {
                        numEdges = checkPixelConnectivity(0, grid[y][x + 1], grid[y + 1][x], grid[y][x - 1]);
                    }
                } else if (y == (colLen - 1)) { // Horizontal bottom boundary.
                    if (x == 0) {               // Bottom left corner.
                        numEdges = checkPixelConnectivity(grid[y - 1][x], grid[y][x + 1], 0, 0);
                    } else if (x == (rowLen - 1)) { // Bottom right corner.
                        numEdges = checkPixelConnectivity(grid[y - 1][x], 0, 0, grid[y][x - 1]);
                    } else {
                        numEdges = checkPixelConnectivity(grid[y - 1][x], grid[y][x + 1], 0, grid[y][x - 1]);
                    }
                } else if (x == 0) { // Vertical left boundary.
                    numEdges = checkPixelConnectivity(grid[y - 1][x], grid[y][x + 1], grid[y + 1][x], 0);
                } else if (x == (rowLen - 1)) { // Vertical right boundary.
                    numEdges = checkPixelConnectivity(grid[y - 1][x], 0, grid[y + 1][x], grid[y][x - 1]);
                }

                if (numEdges > 0) {
                    if (dir == Direction::UP) {
                        hwlib::cout << " up\n";
                        --y;
                    } else if (dir == Direction::RIGHT) {
                        hwlib::cout << " right\n";
                        ++x;
                    } else if (dir == Direction::DOWN) {
                        hwlib::cout << " down\n";
                        ++y;
                    } else {
                        hwlib::cout << " left\n";
                        --x;
                    }

                    numEdges = 0;
                } else {
                    // Terminate both loops.
                    y = colLen;
                    x = rowLen;
                }
            }
        }

        return Pathfinding::Graph();
    }
};

} // namespace Mapping

#endif // MAP_TO_GRAPH_HPP