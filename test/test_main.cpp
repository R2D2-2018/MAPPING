#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/vector2d.hpp"

TEST_CASE("Vector2d", "[Vector2d]")
{
    Mapping::Vector2d vec1(3, 4);
    Mapping::Vector2d vec2(2, 2);

    auto vec3 = vec1 + vec2;

    REQUIRE(vec3.x == 5);
    REQUIRE(vec3.y == 6);
    REQUIRE(vec1.length() == 5);
}
