/**
 * @file
 * @brief     2D map class
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef MAP2D_HPP
#define MAP2D_HPP

#include "angle.hpp"
#include "vector2d.hpp"
#include <array>
#include <math.h>

namespace Mapping {
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
    std::array<std::array<bool, X>, Y> grid;
    Vector2D sensorPosition;

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
    Map2D(Vector2D sensorPosition, double scale) : scale(scale), sensorPosition(sensorPosition) {
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
     * @return [Vector2D] - The current position of the
     * sensor.
     */
    Vector2D getSensorPosition() {
        return sensorPosition;
    }

    /**
     * @brief Moves the sensor with the given delta.
     *
     * @param [in] delta: The change in position
     * of the sensor.
     * NOTE: This value is given in cm, not in grid points!
     */
    void moveSensorCm(Vector2D delta) {
        auto gridVector = Vector2D(round(delta.x / scale), round(delta.y / scale));
        sensorPosition += gridVector;
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
     */
    void moveSensorCm(Angle angle, double distance) {
        //< The compiler does not beleive that the sin() and cos ()functions exists, so this gives an error.
        //< However, if we do something like auto a = sin(distance), then it works
        //< perfectly fine. This should be fixed somehow.

        // moveSensorCm(Vector2D(round(sin(angle.asRadian()) * distance), round(cos(angle.asRadian()) * distance)));
    }

    /**
     * @brief Sets the point as impassable.
     *
     * This function sets the given relative point as
     * impassable.
     *
     * @param [in] point: The to the seensor relative point
     * to be set.
     *
     * NOTE: This value is given in cm, not in grid points!
     */
    void setRelativePointAsImpassable(const Vector2D &point) {
        ///< This should be in a try, but the compiler won't let
        ///< me do that.
        grid.at(sensorPosition.x + (point.x / scale)).at(sensorPosition.y + (point.y / scale)) = true;
    }

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
        ///< The compiler does not beleive that the sin() and cos ()functions exists, so this gives an error.
        ///< However, if we do something like auto a = sin(distance), then it works
        ///< perfectly fine. This should be fixed somehow.

        // setRelativePointAsImpassable(Vector2D(round(sin(angle.asRadian()) * distance), round(cos(angle.asRadian()) * distance)));
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