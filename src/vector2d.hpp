/**
 * @file
 * @brief     2D vector class
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <math.h>

namespace Mapping {
/**
 * @brief This struct represents a point
 * in 2D space. X and y are the coordinates.
 *
 */
struct Vector2D {
    Vector2D(int x, int y) : x(x), y(y) {
    }
    int x;
    int y;

    /**
     * @brief This function calculates the
     * length of the vector.
     *
     * Based on the coordinates, this function
     * calculates and returns the length of the
     * 2D vector.
     *
     * @return [double] - Length of vector.
     */
    double length() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    /**
     * @brief This operator adds up two vectors.
     *
     * This operator adds up two vectors, without
     * modifying them.
     *
     * @return [Vector2D] - New sum vector.
     */
    Vector2D operator+(const Vector2D &other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    /**
     * @brief This operator adds up two vectors.
     *
     * This operator adds a vector to a vector
     * that the function is being called on.
     *
     * @return [Vector2D] - The vector on which
     * the function has been called - the sum vector.
     */
    Vector2D &operator+=(const Vector2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    /**
     * @brief This operator substracts two vectors.
     *
     * This operator substracts vectors, without
     * modifying them.
     *
     * @return [Vector2D] - New difference vector.
     */
    Vector2D operator-(const Vector2D &other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    /**
     * @brief This operator substrats two vectors.
     *
     * This operator substracts a vector from
     * the vector that the function is being called on.
     *
     * @return [Vector2D] - The vector on which
     * the function has been called - the difference vector.
     */
    Vector2D &operator-=(const Vector2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /**
     * @brief This operator multiplies the
     * vector with a scalar value.
     *
     * @return [Vector2D] - The vector on which
     * the function has been called - multiplied vector.
     */
    Vector2D operator*(const int &multiplier) const {
        return Vector2D(x * multiplier, y * multiplier);
    }

    /**
     * @brief This operator multiplies the
     * vector with a scalar value.
     *
     * @return [Vector2D] - Multiplied vector.
     */
    Vector2D &operator*=(const int &multiplier) {
        x *= multiplier;
        y *= multiplier;
        return *this;
    }

    bool operator==(const Vector2D &other) const {
        return other.x == x && other.y == y;
    }
};
} // namespace Mapping

#endif // VECTOR2D_HPP