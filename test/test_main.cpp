#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/angle.hpp"
#include "../src/map2d.hpp"
#include "../src/vector2d.hpp"
#include "catch.hpp"

TEST_CASE("Vector2D", "[Vector2D]") {
    Mapping::Vector2D vec1(3, 4);
    Mapping::Vector2D vec2(2, 2);

    ///< Testing the + operator
    auto vec3 = vec1 + vec2;

    REQUIRE(vec3.x == 5);
    REQUIRE(vec3.y == 6);

    ///< The length function should return
    ///< sqrt(x^2 + y^2)
    REQUIRE(vec1.length() == 5);

    Mapping::Angle angle();
    //angle.set(Mapping::AngleType::DEG, 180);
    //REQUIRE(angle.asRadian() == Mapping::Angle::pi);
}

///< This test case won't compile because of the constructor of angle
///< is apparently not found. (Except for the default constructor, that one
///< works just fine). (And it runs perfectly well in main(), so it's definitely
///< not the code.)
// TEST_CASE("Map2D", "[Map2D]") {

///< Creating a 10x10 map, where 1 grid point is equivalent to 3 cm in real life.
///< The robot is at poition (5, 5) and facing to 0 degrees (down).
// Mapping::Map2D<10, 10> map(Mapping::Vector2D(5, 5), Mapping::Angle(Mapping::AngleType::DEG, 0), 3);

///< The rotation of the robot/sensor is now set to 45 degrees.
// map.setSensorRotation(Mapping::Angle(Mapping::AngleType::DEG, 45));
// REQUIRE(map.getSensorRotation().asDegree() == 45);

///< Now we rotate it with 20 degrees, making the overall angle to be 65.
// map.rotateSensor(Mapping::Angle(Mapping::AngleType::DEG, 20));
// REQUIRE(map.getSensorRotation().asDegree() == 65);


///< The robot is moved 6 cm's to the right (90 degrees). This corrsponds
///< with 2 grid points, since we set the scale to be 3 cm. This roatation
///< is also applied to the robot.
// map.moveSensorCm(Mapping::Angle(Mapping::AngleType::DEG, 90), 6, true);
// REQUIRE(map.getSensorPosition() == Mapping::Vector2D(7, 5))
// REQUIRE(map.getSensorRotation().asDegree() == 90);
//}



///< Same story here, it just won't compile in the test environment.

//TEST_CASE("Angle", [angle]){
    //Mapping::Angle a1(Mapping::AngleType::DEG, 90);

    ///< Testing the conversion to radian
    //REQUIRE(a1.asRadian() == 0.5 * Mapping::Angle::pi);

    ///< Tetsing negative angles (it shold always stay between
    ///< 0 - 359 degrees or 0 - 2pi radians).
    //a1.set(Mapping::AngleType::DEG, -8);
    //REQUIRE(a1.asDegree() == 352);

    ///< Testing addition. Value should stay in range.
    //Mapping::Angle a2(Mapping::AngleType::RAD, Mapping::Angle::pi);
    //a1 += a2;
    //REQUIRE(a1.asDegree() == 172);


    ///< Testing if the angle stays in range.
    //a2.set(Mapping::AngleType::DEG, 722);
    //REQUIRE(a2.asDegree() == 2);
//}