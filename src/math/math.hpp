/*
=============================================================================================
        Author		: Arsalan Anwari
        Library		: Pre-Alpha v1.0 DWARF Lite
        File		: math.hpp
        Part of		: DWARF ENGINE
        Copyright	: https://github.com/ArsalanAnwari/DWARF_ENGINE 2017
        Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================================
*/

#ifndef MATH_HPP
#define MATH_HPP

namespace math {
/**
 * @brief Exponentation of a integer
 * @details This function returns a exponentation of a base by a user defined exponent. \n
 * A technique called bitshifting is used to compare the value of the MSB bit of the exponent. \n
 * If the sum of the mask (0x10) is true, a temporary integer result will be incremented(*=) by the base value. \n
 * By shifting all the bits of the exponent to the right by one, you binary deincrement the value. \n
 * The base gets multiplyplied by it self and the loop proceeds until the binary value of the exponent becomes 0x00
 *
 * @param base
 * @param exp
 * @return integer
 */
int pow(int base, int exp);

/**
 * @brief Exponentation of floating pointer
 * @details This function returns a exponentation of a base by a user defined exponent. \n
 * There are no special techniques being used in this function. just a simple for loop with a result being multiplied by its base.
 *
 * @param base
 * @param exp
 * @return float
 */
float pow(float base, int exp);

/**
 * @brief Calculation of absolute value of a integer
 * @details This function was made by Jens Gustedt
 * @ref https://stackoverflow.com/questions/9772348/get-absolute-value-without-using-abs-function-nor-if-statement
 *
 * @param v
 * @return integer
 */
int abs(int v);
/**
 * @brief Calculation of absolute value of a floatig pointer
 * @details This function was made by Jens Gustedt
 * @ref https://stackoverflow.com/questions/9772348/get-absolute-value-without-using-abs-function-nor-if-statement
 *
 * @param v
 * @return floating pointer
 */
float abs(float v);

/**
 * @brief Two Babylonian Steps (simplfied) square root
 *
 * @param x
 * @return float
 */
float sqrt(const float x);

/**
 * @brief Function used to round a floating pointer up.
 *
 * @param num
 * @return
 */
int ceil(float num);

/**
 * @brief Function used to calculate Bézier points
 * @details In spi_lcd_shapes.hpp and oled_shapes.hpp you are able to make a Bézier based curved lines. \n
 * Here you will generate certain 'bending points' the line had to follow.
 * Bézier was a french engineer who used the Casteljau's algortihm to calculate points of rotation for a straight line. \n
 * The complete explanation of the workings of this point generating method is rather difficult to explain.
 * Please see the link for more info.
 * @ref https://en.wikipedia.org/wiki/B%C3%A9zier_curve
 *
 * @param n1
 * @param n2
 * @param perc
 * @return
 */
int getPt(int n1, int n2, float perc);
/**
 * @brief Simple Factoral calculation of a floating pointer
 *
 * @param x
 * @return float
 */
float fact(int x);

/**
 * @brief Modified Taylor series cos alghorithm
 * @details This is a modified algortihm made by a Professor in MIT. His name was unkown however.
 *
 * @param x
 * @return float
 */
float cos(float x);

/**
 * @brief Modified Taylor series sin alghorithm
 * @details This is a modified algortihm made by a Professor in MIT. His name was unkown however.
 *
 * @param x
 * @return float
 */
float sin(float x);

/**
 * @brief This function will convert a integer to a char array.
 * @details a integer and a char arrray have to be givin to the function. \n
 * The function converts the integer to a char array and will fill the given char array with the content
 *
 * @param n
 * @param ch1
 */
void int_to_string(int n, char ch1[]);

/**
 * @brief This function will return the atan of a float
 *
 * @param inX
 * @return float
 */
float atan(float inX);

/**
 * @brief This function will return the acos of a float
 *
 * @param inX
 * @return float
 */
float acos(float inX);
} // namespace math

#endif // MATH_HPP