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
    return true;
}


int Mapping::Lidar::constructDistance()
{
    return 1;
}


int Mapping::Lidar::constructSignalStrength()
{
    return 1;
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
