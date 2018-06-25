#include "map2d.hpp"
#include "map_to_graph.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    static std::array<std::array<bool, 5>, 5> grid{
        {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}}};

    // Temporarily fixes the problem with the object_pool described below.
    Pathfinding::pathfindingWrap pf;

    Mapping::MapToGraphConverter<std::array<std::array<bool, 5>, 5>> conv(pf);
    conv.convert(grid, 0, 0);

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