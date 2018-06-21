#include "map2d.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    // Mapping::Map2D<10, 10> map(Mapping::Vector2D(5, 5), Mapping::Angle(Mapping::AngleType::DEG, 0), 3);
    // map.getGraph();

    Pathfinding::addNode(0);
    hwlib::cout << Pathfinding::nodePool << '\n';

    return 0;
}
