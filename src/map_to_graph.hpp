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

/**
 * @brief A struct for holding temporary information that will be stored in the stack.
 */
struct tempNode {
    uint8_t pos[2];
    uint8_t new_dir;

    tempNode() : pos{0, 0}, new_dir{0} {
    }

    tempNode(const uint8_t &posY, const uint8_t &posX, const uint8_t &cur) : pos{posY, posX}, new_dir{cur} {
    }
};

template <typename T>
class MapToGraphConverter {
  private:
    Pathfinding::pathfindingWrap &pf;
    uint8_t nodeIndex;

    // Used to 'remember' branches and intersections till they're fully processed.
    Stack<tempNode, 10> stack;

    // Remembers certain nodes to avoid infinite loops.
    std::array<std::array<uint8_t, 2>, 10> nodeMem;
    uint8_t nodeMemIndex;

    // Creates a byte to store the directions.
    // The 4 LSB are the current unvisited edges.
    // Up: 1000, right: 0100, down: 0010, left: 0001.
    // If new_dir == 0 the node has been processed.
    uint8_t prev_dir;
    uint8_t new_dir;

    /**
     * @brief Function for counting set bits.
     *
     * This function uses the Naive algorithm to count set bits. Stops when the byte is 0, should always be <= 4 loops when used to
     count the number of directions.
     *
     * @param[in]   byte    the byte containing the bits.
     * @return The amount of set bits.
     */
    uint8_t countSetBits(uint8_t byte) {
        uint8_t count = 0;
        while (byte) {
            count += (byte & 1);
            byte >>= 1;
        }
        return count;
    }

    /**
     * @brief Function used to prevent the algorithm from going back from where it came.
     *
     * This function unsets a certain bit depending on the 'old' parameter. For example:
     * We move downwards to an intersection, the top 'bit' will be unset.
     * d(0010) -> i(1111) = 0111
     *
     * @param[in]   old    the old value used to unset a certain bit.
     * @param[out]  cur    the new value where the bit is set to 0.
     */
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

    /**
     * @brief Checks whether an element is in the nodeMem matrix.
     *
     * This function checks if important nodes are in the nodeMem matrix.
     * This is required to avoid infinite loops.
     *
     * @param[in]   y    The y coordinate to be checked.
     * @param[in]  x    The x coordinate to be checked.
     * @return returns true if the item is present in the matrix.
     */
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

    /**
     * @brief Checks whether a pixel has edges.
     *
     * This function checks for 'true' values in a 4-connected neighborhood.
     *
     * @param[in]   up      The value stored in the index above it.
     * @param[in]   right   The value stored in the index on the right of it.
     * @param[in]   down    The value stored in the index below it.
     * @param[in]   left    The value stored in the index on the left of it.
     * @return returns the number of detected edges.
     */
    uint8_t checkPixelConnectivity(const bool &up, const bool &right, const bool &down, const bool &left) {
        uint8_t numEdges = 0;
        if (up) {
            new_dir |= 0x08;
            ++numEdges;
        }
        if (right) {
            new_dir |= 0x04;
            ++numEdges;
        }
        if (down) {
            new_dir |= 0x02;
            ++numEdges;
        }
        if (left) {
            new_dir |= 0x01;
            ++numEdges;
        }
        return numEdges;
    }

  public:
    MapToGraphConverter(Pathfinding::pathfindingWrap &pf) : pf{pf}, nodeIndex{0}, nodeMemIndex{0}, prev_dir{0}, new_dir{0} {
    }

    MapToGraphConverter(const T &grid, Pathfinding::pathfindingWrap &pf, const uint8_t &startY, const uint8_t &startX)
        : pf{pf}, nodeIndex{0}, nodeMemIndex{0}, prev_dir{0}, new_dir{0} {
        convert(grid, startY, startX);
    }

    /**
     * @brief The main function that creates the nodes and calls the correct functions.
     *
     * This function turns a boolean/bindary matrix into a graph.
     *
     * @param[in]   grid        The grid that will be converted.
     * @param[in]   startY      The Y coordinate starting position.
     * @param[in]   startX      The x coordinate starting position.
     */
    void convert(const T &grid, const uint8_t &startY, const uint8_t &startX) {
        uint8_t colLen = grid.size();
        uint8_t rowLen = grid[0].size();

        uint8_t numEdges = 0;
        tempNode tn;
        uint8_t temp_dir;
        for (uint8_t y = startY; y < colLen;) {
            for (uint8_t x = startX; x < rowLen;) {

                //< Checks if the index is within the boundaries to avoid undefined behaviour.
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

                //< Checks for important nodes to store them.
                if ((numEdges > 2) || (startY == y && startX == x)) {
                    if (!checkNodeMem(y, x)) {
                        nodeMem[nodeMemIndex++] = {y, x};
                        disablePrevDirection(prev_dir, new_dir);
                        temp_dir = new_dir;

                        ///< Disables one bit before moving in that direction.
                        if (new_dir > 7) {
                            temp_dir &= 0xF7;
                        } else if (new_dir > 3) {
                            temp_dir &= 0xFB;
                        } else if (new_dir > 1) {
                            temp_dir &= 0xFD;
                        } else {
                            temp_dir &= 0xFE;
                        }

                        stack.push(tempNode(y, x, temp_dir));
                    } else {
                        if (checkNodeMem(y, x)) {
                            tn = stack.pop();
                            new_dir = tn.new_dir;
                        }
                        disablePrevDirection(prev_dir, new_dir);
                    }
                } else {
                    disablePrevDirection(prev_dir, new_dir);
                }

                //< Checks whether a direction has finished or an important node has been processed.
                if (countSetBits(new_dir) == 0) {
                    if (!stack.isEmpty()) {
                        tn = stack.peek();
                        y = tn.pos[0];
                        x = tn.pos[1];
                        new_dir = tn.new_dir;

                        if (countSetBits(tn.new_dir) < 2) {
                            stack.pop();
                        } else {
                            temp_dir = new_dir;

                            // Disables one bit before moving in that direction.
                            if (new_dir > 7) {
                                temp_dir &= 0xF7;
                            } else if (new_dir > 3) {
                                temp_dir &= 0xFB;
                            } else if (new_dir > 1) {
                                temp_dir &= 0xFD;
                            } else {
                                temp_dir &= 0xFE;
                            }
                            stack.peekRef().new_dir = temp_dir;
                        }
                    }
                }

                ///< Changes the index depending on the bits stores in the new_dir byte.
                if (new_dir > 0) {
                    if (new_dir > 7) {
                        --y;
                    } else if (new_dir > 3) {
                        ++x;
                    } else if (new_dir > 1) {
                        ++y;
                    } else {
                        --x;
                    }

                    prev_dir = new_dir;
                    new_dir = 0;
                } else {
                    if (stack.isEmpty()) {
                        y = colLen;
                        break;
                    }
                }
            }
        }
    }
};

} // namespace Mapping

#endif // MAP_TO_GRAPH_HPP