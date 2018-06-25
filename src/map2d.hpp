/**
 * @file
 * @brief     2D map class
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef MAP2D_HPP
#define MAP2D_HPP

#include "angle.hpp"
#include "math/math.hpp"
#include "math/round.hpp"
#include "vector2d.hpp"
#include "wrap-hwlib.hpp"
#include <array>

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
