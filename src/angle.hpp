/**
 * @file
 * @brief     Angle class
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef ANGLE_HPP
#define ANGLE_HPP

namespace Mapping {
enum class AngleType { DEG, RAD };

/**
 * @class This class stores an angle between 0-360 degree
 * /0 - 2pi radian.
 */
class Angle {
  private:
    double angleInDeg;

  public:
    static const double pi;
    /**
     * @brief ctor
     *
     * Default constructor of the angle class. This will
     * initialize the angle as 0 degrees.
     *
     */
    Angle();

    /**
     * @brief ctor
     *
     * This constructor stores the given angle. The angle
     * will be capped in valid range (0 - 360 degrees or
     * 0 - 2pi radians).
     *
     * @param [in] type: Specifies the unit of the
     * angle value that is given.
     *
     * @param [in] value: The value of the angle. Note:
     * this can be any number, but it will be capped
     * in valid range.
     */
    Angle(AngleType type, double value);

    /**
     * @brief Sets a new angle.
     *
     * This function allows the user to store a new
     * angle value in the object.
     *
     * @param [in] type: Specifies the unit of the
     * angle value that is given.
     *
     * @param [in] value: The value of the angle. Note:
     * this can be any number, but it will be capped
     * in valid range.
     */
    void set(AngleType type, double value);

    /**
     * @brief Returns the stored angle as  degree.
     *
     *
     * @return [double] - The stored angle as degree.
     * The value will be between 0 - 360.
     */
    double asDegree();

    /**
     * @brief Returns the stored angle as radian.
     *
     *
     * @return [double] - The stored angle as radian.
     * The value will be between 0 - 2pi.
     */
    double asRadian();

    /**
     *
     * @brief += operator for angle.
     *
     */
    Angle &operator+=(const Angle &other);

    /**
     *
     * @brief + operator for angle.
     *
     */
    Angle operator+(const Angle &other);

    /**
     *
     * @brief -= operator for angle.
     *
     */
    Angle &operator-=(const Angle &other);

    /**
     *
     * @brief - operator for angle.
     *
     */
    Angle operator-(const Angle &other);
};
} // namespace Mapping

#endif // ANGLE_HPP