#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/vector2d.hpp"
#include "../src/map2d.hpp"
#include "../src/angle.hpp"

TEST_CASE("Vector2d", "[Vector2d]")
{
    Mapping::Vector2d vec1(3, 4);
    Mapping::Vector2d vec2(2, 2);

    auto vec3 = vec1 + vec2;

    REQUIRE(vec3.x == 5);
    REQUIRE(vec3.y == 6);
    REQUIRE(vec1.length() == 5);
}


TEST_CASE("Map2d", "[Map2d]")
{
    Mapping::Map2d<10, 10> map(Mapping::Vector2d(5, 5), 3);

    //Set sensor pos to [3, 2];
    map.moveSensorCm(Mapping::Vector2d(-6, -9));
    REQUIRE(map.getSensorPosition().x == 3);
    REQUIRE(map.getSensorPosition().y == 2);

    //Set [4, 3] as impassable
    map.setRelativePointAsImpassable(Mapping::Vector2d(3, 3));
    REQUIRE(map.getGrid()[4][3] == true);
}
