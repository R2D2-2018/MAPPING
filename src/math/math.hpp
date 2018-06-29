#ifndef MATH_HPP
#define MATH_HPP

/**
 * @file        math.hpp
 * @brief       Math class
 * @author      Arsalan Anwari
 * @license     See LICENSE and http://www.boost.org/LICENSE_1_0.txt
 */

namespace math {
/**
 * @brief Exponentation of an integer
 * @details This function returns an exponentation of a base by a user defined exponent. \n
 * A technique called bitshifting is used to compare the value of the MSB bit of the exponent. \n
 * If the sum of the mask (0x10) is true, a temporary integer result will be incremented(*=) by the base value. \n
 * By shifting all the bits of the exponent to the right by one, you deincrement the value. \n
 * The base gets multiplied by itself and the loop proceeds until the binary value of the exponent becomes 0x00.
 *
 * @param[in] base The base number to be raised to the power of the exponent
 * @param[in] exp The exponent
 * @return integer The base number raised to the power of the exponent
 */
int pow(int base, int exp);

/**
 * @brief Exponentation of floating pointer
 * @details This function returns an exponentation of a base value by a user defined exponent. \n
 * There are no special techniques being used in this function. just a simple for loop multiplying the base value by itself.
 *
 * @param[in] base The base number to be raised to the power of the exponent
 * @param[in] exp The exponent
 * @return float The base number raised to the power of the exponent
 */
float pow(float base, int exp);

/**
 * @brief Calculation of absolute value of a integer
 * @details This function was made by Jens Gustedt
 * @ref https://stackoverflow.com/questions/9772348/get-absolute-value-without-using-abs-function-nor-if-statement
 *
 * @param[in] v The value to be made absolute
 * @return integer The absolute value
 */
int abs(int v);
/**
 * @brief Calculation of absolute value of a floatig pointer
 * @details This function was made by Jens Gustedt
 * @ref https://stackoverflow.com/questions/9772348/get-absolute-value-without-using-abs-function-nor-if-statement
 *
 * @param[in] v The value to be made absolute
 * @return float The absolute value
 */
float abs(float v);

/**
 * @brief Two Babylonian Steps (simplfied) square root
 * @details This function calculates the square root of a given value using the Two Babylonian Steps algorithm.
 *
 * @param[in] x The value of which we will calculate the square root.
 * @return float The square-rooted value from the parameter.
 */
float sqrt(const float x);

/**
 * @brief Round a floating pointer up.
 *
 * @param[in] num The number to be rounded up.
 * @return int The rounded up number.
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
 * @param[in] n1
 * @param[in] n2
 * @param[in] perc
 * @return int
 */
int getPt(int n1, int n2, float perc);
/**
 * @brief Simple Factoral calculation of a floating pointer
 *
 * @param[in] x
 * @return float
 */
float fact(int x);

/**
 * @brief Modified Taylor series cos alghorithm
 * @details This is a modified algortihm made by a Professor in MIT. His name was unkown however.
 *
 * @param[in] x
 * @return float
 */
float cos(float x);

/**
 * @brief Modified Taylor series sin alghorithm
 * @details This is a modified algortihm made by a Professor in MIT. Unfortunately his name is unknown.
 *
 * @param[in] x
 * @return float
 */
float sin(float x);

/**
 * @brief This function will convert a integer to a char array.
 * @details a integer and a char arrray have to be givin to the function. \n
 * The function converts the integer to a char array and will fill the given char array with the content
 *
 * @param[in] n
 * @param[in] ch1
 */
void intToString(int n, char ch1[]);

/**
 * @brief This function will return the atan of a float
 *
 * @param[in] inX
 * @return float
 */
float atan(float inX);

/**
 * @brief This function will return the acos of a float
 *
 * @param[in] inX
 * @return float
 */
float acos(float inX);
} // namespace math

#endif // MATH_HPP