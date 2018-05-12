#include "mock_pin.hpp"


std::array<bool, 72> Mapping::MockPin::answers = std::array<bool, 72> {
    0, 0, 1, 1, 1, 0, 1, 1, //Startbit 59
    0, 0, 1, 1, 1, 0, 1, 1, //Startbit 59
    0, 0, 0, 0, 0, 0, 1, 1, // Distance low 3
    0, 0, 0, 0, 0, 0, 0, 1, // Distance high 256 (1)
    0, 0, 0, 0, 0, 1, 1, 1, // Strength low 7
    0, 0, 0, 0, 0, 0, 1, 0, // Strength high 512 (2)
    0, 0, 0, 0, 0, 0, 0, 0, // Integration time 0
    0, 0, 0, 0, 0, 0, 0, 0, // Reserved 0
    1, 0, 0, 0, 0, 0, 1, 1  // Checksum 131
};


Mapping::MockPin::MockPin():
    hwlib::target::pin_in(hwlib::target::pins::d12),
    counter(0)
{}


bool Mapping::MockPin::get(hwlib::buffering buf)
{
    return answers[counter++];
}