/**
 * @file
 * @brief     Interface class for Lidar sensor tfmini
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef LIDAR_HPP
#define LIDAR_HPP
#include "../wrap-hwlib.hpp"
#include "lidar_data.hpp"
#include <array>


namespace Mapping
{
    class Lidar
    {
    private:
        hwlib::target::pin_in& pin;
        int numberOfTries;
        std::array<char, 7> bytes;

          /**
         * @brief This function reads and returns
         * the value of the object's pin.
         * 
         * This function reads the arduino pin
         * after sleeping some time, to ensure that the
         * frequency of readings matches with the baud 
         * rate of the sensor.
         * WAIT IS NOT IMPLEMENTED YET!
         * 
         * @return The value of the pin 1 - on, 0 - off
         */
        bool getPin();

         /**
         * @brief This function reads a byte from the pin.
         * 
         * This function reads Lidar::pin 8 times, and returns
         * those as a char.
         * 
         * @return The readings as a char. MSB is the first reading.
         */
        char getByte();

          /**
         * @brief This function will return when the start 
         * of a frame is found.
         * 
         * This function will not return until two bytes
         * with value 59 are found in a row OR the specified
         * number of tries expires. In that case an exception
         * will be thrown.
         */
        void waitForStart();

          /**
         * @brief This function checks whether the checksum 
         * correct is.
         * 
         * This function is to be called when a whole frame
         * is received. It will return whether the checksum 
         * correct is.
         * 
         * @return true - message is ok, false - message is not ok
         */
        bool check();

          /**
         * @brief This function returns the distance data.
         * 
         * The distance data is constructed from the distance
         * high and distance low bytes.
         * 
         * @return distance in cm
         */
        int constructDistance();

        /**
         * @brief This function returns the signal strength data.
         * 
         * The signal strength data is constructed from the
         * signal strengthhigh and signal strength low bytes.
         * 
         * @return signal strength
         */
        int constructSignalStrength();

    public:
        Lidar(hwlib::target::pin_in& pin, int numberOfTries);

        LidarData getLidarData();
    };
}

#endif // LIDAR_HPP
