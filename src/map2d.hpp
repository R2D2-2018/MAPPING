/**
 * @file
 * @brief     2D map class
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef MAP2D_HPP
#define MAP2D_HPP

#include "Pathfinding_mock/pathfinding.hpp"
#include "angle.hpp"
#include "math/math.hpp"
#include "math/round.hpp"
#include "vector2d.hpp"
#include "wrap-hwlib.hpp"
#include <array>

namespace Mapping {
// Used for map to graph conversion, to remember visited/unvisited directions while moving through the matrix.
enum class Direction { UP, RIGHT, DOWN, LEFT };
Direction dir;
Direction oppDir;

// Test grid. 72 1s.
static std::array<std::array<bool, 13>, 13> test_grid{{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                       {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                                                       {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                                                       {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
                                                       {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                                                       {0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
                                                       {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                                       {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
                                                       {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                                       {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                                                       {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                       {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
                                                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};

/**
 * @brief This class represents a 2d map.
 *
 * The map is used to save the 2D scanned map
 * of the environment. It contains a 2D bool array,
 * where the x coordinatey corresponds to the horizontal
 * direction, pointing left, and the y coordinate corresponds
 * to the vertical direction, pointing down.
 * 0 ---> X
 * |
 * |
 * V Y
 *
 * All the grid points of the map are by default false. When a
 * point is set to true, it means that the there is an obstacle detected,
 * the point is impassable by the robot.
 *
 * Angle 0 is pointing downwards, and grows counterclockwise.
 *       180
 *        A
 * 	      |
 * -90<---o---> 90
 *        |
 *        V
 *        0
 */
template <int X, int Y>
class Map2D {
  private:
    double scale;
    Angle sensorAngle;
    std::array<std::array<bool, X>, Y> grid;
    Vector2D sensorPosition;

    /**
     * @brief Sets the point as impassable.
     *
     * This function sets the given relative point as
     * impassable.
     *
     * @param [in] angle: The angle in which in the direction
     * of the to bet set point. Angle 0 is pointing downwards, and
     * grows counterclockwise.
     *
     *  @param [in] distance: The distance of the point to the
     *
     * NOTE: This value is given in cm, not in grid points!
     */
    void setRelativePointAsImpassable(Angle angle, double distance) {
        auto absoluteVector =
            Vector2D(math::round(math::sin(angle.asRadian()) * distance), math::round(math::cos(angle.asRadian()) * distance));
        grid[sensorPosition.x + (absoluteVector.x / scale)][sensorPosition.y + (absoluteVector.y / scale)] = true;
    }

    // Logic function for moving through the matrix.
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

    // Checks how a pixel is connected and calls the appropriate functions with certain parameters.
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

        // Order of if statements can be changed to improve performance.
        if (edges == 1) {
            hwlib::cout << "o";  // End
        } else if (edges == 2) { // Corner or line
            if (top & bottom) {  // Vertical line
                hwlib::cout << "|";
            } else if (right & left) { // Horizontal line
                hwlib::cout << "-";
            } else { // Corner
                hwlib::cout << "o";
            }
        } else if (edges == 3) {
            hwlib::cout << "o"; // Branch
        } else if (edges == 4) {
            hwlib::cout << "o"; // Intersection
        } else {
            hwlib::cout << "x"; // Alone
        }

        return edges;
    }

  public:
    /**
     * @brief ctor
     *
     * Constructs a new, empty map with the given dimensions.
     * The position of the sensor can be set, so when
     * an obstacle is detected the it will know where to put
     * it on the map. (All positions are valid positions for the
     * sensor, including those outside of the map.)
     * The scale tells how many real life centimeter does
     * a grid point represent. This way the distance data
     * input can be given in centimeters.
     *
     * @param [in] sensorPosition: The position of the
     * sensor relative to the to be mapped area.
     *
     * @param [in] scale: 1 grid distance = scale * 1 cm
     */
    Map2D(Vector2D sensorPosition, Angle sensorAngle, double scale)
        : scale(scale), sensorAngle(sensorAngle), sensorPosition(sensorPosition) {
        clear();
    }

    /**
     * @brief Gets the map
     *
     * This function returns the map (read  only).
     * The first coordinat of the array is the position
     * along the X axis, the second is the position along
     * the Y axis.
     * A grid point is false when it is not set, and
     * true when it is set as obstacle.
     *
     * @return [std::array<std::array<bool, X>, Y>&] - the map
     */
    const std::array<std::array<bool, X>, Y> &getGrid() const {
        return grid;
    }

    /**
     * @brief Gets the map as a Graph
     *
     * This function returns the created map as a
     * Pathfinding::Graph.
     * This is a dummy implementation, that returns
     * an empty graph. The Graph data type is being
     * currently further developed by the team
     * responisble for pathfinding.
     *
     * @return [out] - the map as a graph
     */
    Pathfinding::Graph getGraph(Pathfinding::pathfindingWrap &pf) {
        uint8_t colLen = test_grid.size();
        uint8_t rowLen = test_grid[0].size();

        uint8_t numEdges;

        // Very early implementation, does not work with boundaries yet nor does it work with branches and intersections.
        bool *ptr = &test_grid[1][1];
        bool first = true; // Temporary
        while (*ptr) {
            numEdges = checkPixelConnectivity(*(ptr - rowLen), *(ptr + 1), *(ptr + rowLen), *(ptr - 1));
            if ((numEdges == 2) || first) {
                if (Mapping::dir == Mapping::Direction::UP) {
                    hwlib::cout << " up\n";
                    ptr -= rowLen;
                } else if (Mapping::dir == Mapping::Direction::RIGHT) {
                    hwlib::cout << " right\n";
                    ptr += 1;
                } else if (Mapping::dir == Mapping::Direction::DOWN) {
                    hwlib::cout << " down\n";
                    ptr += rowLen;
                } else if (Mapping::dir == Mapping::Direction::LEFT) {
                    hwlib::cout << " left\n";
                    ptr -= 1;
                }
                first = false;
            } else {
                if (!first)
                    break;
            }
        }

        return Pathfinding::Graph();
    }

    /**
     * @brief Sets the position of the sensor.
     *
     * This function sets the position of the
     * sensor to the given absolute location.
     * If you wish to move the sensor with a delta instead,
     * use moveSensorCm()
     *
     * @param [in] newPosition: The new absolute position of the
     * sensor.
     */
    void setSensorPosition(Vector2D newPosition) {
        sensorPosition = newPosition;
    }

    /**
     * @brief Returns the current position of the sensor.
     *
     * @return [out] - The current position of the
     * sensor.
     */
    Vector2D getSensorPosition() {
        return sensorPosition;
    }

    /**
     * @brief Returns the current rotation of the sensor.
     */
    Angle getSensorRotation() {
        return sensorAngle;
    }

    /**
     * @brief Moves the sensor with the given delta.
     *
     * @param [in] angle: The angle in which the position
     * is changed. Angle 0 is pointing downwards, and
     * grows counterclockwise.
     *
     * @param [in] distance: The distance delta
     * of the sensor in centimeters.
     * NOTE: This value is given in cm, not in grid points!
     *
     * @param [in] setRotation: If true, de angle will be set
     * as the angle of the sensor.
     */
    void moveSensorCm(Angle angle, double distance, bool setRotation = false) {
        auto absolutVector =
            Vector2D(math::round(math::sin(angle.asRadian()) * distance), math::round(math::cos(angle.asRadian()) * distance));
        sensorPosition += Vector2D(math::round(absolutVector.x / scale), math::round(absolutVector.y / scale));
        if (setRotation) {
            sensorAngle = angle;
        }
    }

    /**
     * @brief This function rotates the sensor with
     * the given angle.
     *
     * @param [in] delta: The change in rotation.
     */
    void rotateSensor(Angle delta) {
        sensorAngle += delta;
    }
    /**
     * @brief This function sets the rotation of the sensor
     * to the given (absolute) value.
     *
     * @param [in] angle: The absolut angle of the sensor.
     */
    void setSensorRotation(Angle angle) {
        sensorAngle = angle;
    }

    /**
     * @brief This function maps the location in
     * 360 degrees, and fills the detected points in.
     * This method uses the servo motor controller to set
     * specified angles of the lidar sensor. This will be
     * delivered by the module motor controller.
     *
     * The driver to the lidar sensor that allows us to
     * read the measured distance, will be developed by
     * the team that is responsible for distance measurement.
     */
    void mapLocation() {
        ///< The servo motor will be called here. Waitnig for team motor controller
        for (int i = 0; i < 360; ++i) {
            ///< servo.write(i)
            ///< auto measuredDistance = lidar.read();
            ///< if (measuredDistance < MAX_VALUE_OF_SENSOR){
            ///<    setRelativePointasImpassable(Angle(AngleType::DEG, i + sensorAngle.asRadian()), measuredDistance)
            ///<}
        }
    }

    /**
     * @brief Resets the map.
     *
     * All the grid points will be false.
     */
    void clear() {
        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                grid[i][j] = false;
            }
        }
    }
};
} // namespace Mapping

#endif // MAP2D_HPP
