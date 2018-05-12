#include "lidar.hpp"


Mapping::Lidar::Lidar(hwlib::target::pin_in& pin, int numberOfTries = 1000):
    pin(pin),
    numberOfTries(numberOfTries)
{}


bool Mapping::Lidar::getPin()
{
    //wait
    return !pin.get();
}


char Mapping::Lidar::getByte()
{
    char result = 0;
    for (int i = 0; i < 8; ++i)
    {
        result *= 10;
        result += getPin();
    }
    return result;
}


Mapping::LidarData Mapping::Lidar::getLidarData()
{
    Mapping::LidarData data;
    waitForStart();
    for (int i = 0; i < 7; ++i)
    {
        bytes[i] = getByte();
    }
    if (check())
    {
        data.distance = constructDistance();
        data.signalStrength = constructSignalStrength();
    }
    else
    {
        //exception
    }
    return data;
}


bool Mapping::Lidar::check()
{
    char checksum = 0;
    for (int i = 0; i < 6; ++i)
    {
        checksum += bytes[i];
    }
    ///< Byte 1&2 are both 59 (startbit)
    checksum += 118;
    return checksum == bytes[6];
}


int Mapping::Lidar::constructDistance()
{
    int distance = bytes[1];
    distance <<= 8;
    distance += bytes[0];
    return distance;
}


int Mapping::Lidar::constructSignalStrength()
{
    int strength = bytes[3];
    strength <<= 8;
    strength += bytes[2];
    return strength;
}


void Mapping::Lidar::waitForStart()
{
    char buffer = 255;
    for (int t = 0; t < numberOfTries; ++t)
    {
        buffer <<= 1;
        buffer = buffer | getPin();
        if (buffer == 59)
        {
            for (int i = 0; i < 8; ++i)
            {
                getPin();
            }
            if (buffer == 59)
            {
                return;
            }
        }
    }
}
