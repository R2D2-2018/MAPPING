#include "lidar.hpp"


Mapping::Lidar::Lidar(hwlib::target::pin_in pin):
    pin(pin)
{}


char Mapping::Lidar::getByte()
{
    char result = 0;
    for (int i = 0; i < 8; ++i)
    {
        result *= 10;
        result += pin.get();
    }
    return result;
}
