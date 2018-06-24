/**
 * @file      map_to_graph.hpp
 * @brief     Class for the conversion of a boolean/binary matrix to a graph.
 * @author    Nick Swaerdens
 * @license   See LICENSE
 */

#ifndef MAP_TO_GRAPH_HPP
#define MAP_TO_GRAPH_HPP

#include "Pathfinding_mock/pathfinding.hpp"
#include "stack.hpp"
#include "wrap-hwlib.hpp"
#include <array>

namespace Mapping {

struct tempNode {
    uint8_t pos[2];
    uint8_t prev_dir;
    uint8_t new_dir;

    tempNode() : pos{0, 0}, prev_dir{0}, new_dir{0} {
    }

    tempNode(const uint8_t &posY, const uint8_t &posX, const uint8_t &prev, const uint8_t &cur)
        : pos{posY, posX}, prev_dir{prev}, new_dir{cur} {
    }
};

template <typename T>
class mapToGraphConverter {
  private:
    Pathfinding::pathfindingWrap &pf;
    Stack<tempNode, 10> stack; // Stack is used to return to branches/intersections after a direction has been completed.
    std::array<std::array<uint8_t, 2>, 10> nodeMem; // Remembers certain nodes to avoid infinite loops.

    uint8_t nodeIndex;

    // Creates a byte to store the directions.
    // The 4 LSB are the current unvisited edges.
    // Up: 1000, right: 0100, down: 0010, left: 0001.
    // If new_dir == 0 the node has been processed.
    uint8_t prev_dir;
    uint8_t new_dir;

    // Hamming weight, Naive algorithm for counting the set bits.
    // Stops when the digit is 0, should always be <= 4 loops when used to count number of directions.
    uint8_t countSetBits(uint8_t dir) {
        uint8_t count = 0;
        while (dir) {
            count += (dir & 1);
            dir >>= 1;
        }
        return count;
    }

    // Prevents going back.
    // Example:
    // We move downwards to an intersection, the top 'bit' will be unset.
    // d(0010) -> i(1111) = 0111
    void disablePrevDirection(const uint8_t &old, uint8_t &cur) {
        if (old > 7) {
            cur &= 0xFD;
        } else if (old > 3) {
            cur &= 0xFE;
        } else if (old > 1) {
            cur &= 0xF7;
        } else if (old > 0) {
            cur &= 0xFB;
        }
    }

    // Checks whether an element is in the nodeMem matrix.
    bool checkNodeMem(const uint8_t &y, const uint8_t &x) {
        bool infinite = false;
        for (uint8_t i = 0; i < nodeMem.size(); ++i) {
            if (nodeMem[i][0] == y) {
                for (uint8_t j = 0; j < nodeMem[i].size(); ++j) {
                    if (nodeMem[j][1] == x) {
                        infinite = true;
                    }
                }
            }
        }
        return infinite;
    }

    // Check pixel connectivity.
    void checkPixelConnectivity(const bool &up, const bool &right, const bool &down, const bool &left) {
        if (up) {
            new_dir |= 0x08;
        }
        if (right) {
            new_dir |= 0x04;
        }
        if (down) {
            new_dir |= 0x02;
        }
        if (left) {
            new_dir |= 0x01;
        }

        uint8_t edges = countSetBits(new_dir);
        disablePrevDirection(prev_dir, new_dir);

        // Order of if statements should be optimized.
        if (edges == 1) { // End
            hwlib::cout << "o";
            ++nodeIndex;
        } else if (edges == 2) { // Corner or line
            if (up & down) {     // Vertical line
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
        } else { // Alone
            hwlib::cout << "x";
        }
    }

  public:
    mapToGraphConverter(Pathfinding::pathfindingWrap &pf) : pf{pf}, nodeIndex{0}, prev_dir{0xFF}, new_dir{0} {
    }

    mapToGraphConverter(T &grid, Pathfinding::pathfindingWrap &pf, const uint8_t &startY, const uint8_t &startX)
        : pf{pf}, nodeIndex{0}, prev_dir{0xFF}, new_dir{0} {
        convert(grid, startY, startX);
    }

    Pathfinding::Graph convert(T &grid, const uint8_t &startY, const uint8_t &startX) {
        uint8_t colLen = grid.size();
        uint8_t rowLen = grid[0].size();

        // Turn grid[startY][startX] into a node before conversion.
        new_dir = 0x02;
        prev_dir = 0x02;

        for (uint8_t y = startY; y < colLen;) {
            for (uint8_t x = startX; x < rowLen;) {
                // If not on the boundaries.
                if (((y > 0) & (x > 0)) && ((y < (colLen - 1)) & (x < (rowLen - 1)))) {
                    checkPixelConnectivity(grid[y - 1][x], grid[y][x + 1], grid[y + 1][x], grid[y][x - 1]);
                } else if (y == 0) { // Horizontal top boundary.
                    if (x == 0) {    // Top left corner.
                        checkPixelConnectivity(0, grid[y][x + 1], grid[y + 1][x], 0);
                    } else if (x == (rowLen - 1)) { // Top right corner.
                        checkPixelConnectivity(0, 0, grid[y + 1][x], grid[y][x - 1]);
                    } else {
                        checkPixelConnectivity(0, grid[y][x + 1], grid[y + 1][x], grid[y][x - 1]);
                    }
                } else if (y == (colLen - 1)) { // Horizontal bottom boundary.
                    if (x == 0) {               // Bottom left corner.
                        checkPixelConnectivity(grid[y - 1][x], grid[y][x + 1], 0, 0);
                    } else if (x == (rowLen - 1)) { // Bottom right corner.
                        checkPixelConnectivity(grid[y - 1][x], 0, 0, grid[y][x - 1]);
                    } else {
                        checkPixelConnectivity(grid[y - 1][x], grid[y][x + 1], 0, grid[y][x - 1]);
                    }
                } else if (x == 0) { // Vertical left boundary.
                    checkPixelConnectivity(grid[y - 1][x], grid[y][x + 1], grid[y + 1][x], 0);
                } else if (x == (rowLen - 1)) { // Vertical right boundary.
                    checkPixelConnectivity(grid[y - 1][x], 0, grid[y + 1][x], grid[y][x - 1]);
                }

                if (new_dir > 0) {
                    if (new_dir == 0x08) {
                        hwlib::cout << " up\n";
                        --y;
                    } else if (new_dir == 0x04) {
                        hwlib::cout << " right\n";
                        ++x;
                    } else if (new_dir == 0x02) {
                        hwlib::cout << " down\n";
                        ++y;
                    } else if (new_dir) {
                        hwlib::cout << " left\n";
                        --x;
                    }

                    prev_dir = new_dir;
                    new_dir = 0;
                } else {
                    hwlib::cout << " end\n";

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