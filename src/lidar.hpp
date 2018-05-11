/**
 * @file
 * @brief     Interface class for Lidar sensor tfmini
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef LIDAR_HPP
#define LIDAR_HPP
#include "wrap-hwlib.hpp"


namespace Mapping
{
    class Lidar
    {
    private:
        hwlib::target::pin_in pin;

        /**
         * @brief This function reads a byte from the pin.
         * 
         * This function reads Lidar::pin 8 times, and returns
         * those as a char. IMPORTANT: there is no delay added
         * yet, so the next reading happens right after the previous.
         * A delay need to be added in order to match with the
         * sensor's baud rate (115200)
         * 
         * @return The readings as a char. MSB is the first reading.
         */
        char getByte();

    public:
        Lidar(hwlib::target::pin_in pin);
    };
}

#endif // LIDAR_HPP
