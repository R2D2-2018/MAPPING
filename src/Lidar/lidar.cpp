#include "lidar.hpp"


Mapping::Lidar::Lidar(hwlib::target::pin_in& pin, int numberOfTries = 100):
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
    return Mapping::LidarData();
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
    
}
