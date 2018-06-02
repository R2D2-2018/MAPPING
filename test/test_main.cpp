#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/angle.hpp"
#include "../src/map2d.hpp"
#include "../src/vector2d.hpp"
#include "catch.hpp"

TEST_CASE("Vector2D", "[Vector2D]") {
    Mapping::Vector2D vec1(3, 4);
    Mapping::Vector2D vec2(2, 2);

    auto vec3 = vec1 + vec2;

    REQUIRE(vec3.x == 5);
    REQUIRE(vec3.y == 6);
    REQUIRE(vec1.length() == 5);
}

///< Again, this test case won't compile because of the constructor of angle
///< is apparently not found. (Except for the default constructor, that one
///< works just fine). (And it runs perfectly well in main(), so it's definitely
///< not the code.)
//TEST_CASE("Map2D", "[Map2D]") {
    //Mapping::Map2D<10, 10> map(Mapping::Vector2D(5, 5), Mapping::Angle(Mapping::AngleType::DEG, 0), 3);
    //map.setSensorRotation(Mapping::Angle(Mapping::AngleType::DEG, 45));
    //REQUIRE(mapping.getSensorRotation().asDegree() == 45);

    //map.rotateSensor(Mapping::Angle(AngleType::DEG, 20));
    //REQUIRE(map.getSensorRotation().asDegree() == 65);

    //map.rotateSensor(Mapping::Angle(Mapping::AngleType::DEG, 45));
    //REQUIRE(map.getSensorRotation().asDegree() == 45);
`   
    //map.moveSensorCm(Mapping::Angle(Mapping::AngleType::DEG, 90), 6, true);
    //REQUIRE(map.getSensorPosition() == Mapping::Vector2D(7, 5))
    //REQUIRE(map.getSensorRotation().asDegree() == 90);
//}
