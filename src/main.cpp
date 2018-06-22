#include "map2d.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    // Temporarily fixes the problem with the object_pool described below.
    Pathfinding::pathfindingWrap pf;

    Mapping::Map2D<10, 10> map(Mapping::Vector2D(5, 5), Mapping::Angle(Mapping::AngleType::DEG, 0), 3);
    map.getGraph(pf);

    /*
    // ObjectPool<char, 64> in pathfinding.hpp
    hwlib::cout << Pathfinding::nodePool << '\n';
    // 0000000000000000000000000000000000000000000000000000000000000000

    Pathfinding::ObjectPool<char, 64> pool = {};
    hwlib::cout << pool << '\n';
    // 1111111111111111111111111111111111111111111111111111111111111111
    */
    return 0;
}