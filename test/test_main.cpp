#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/Lidar/Mock/mock_pin.hpp"

TEST_CASE( "Mapping::Lidar::getLidarData()" ) 
{
    Mapping::MockPin mp;
    Mapping::Lidar lidar(mp);
    auto data = lidar.getLidarData();
    REQUIRE(data.distance == 259);
    REQUIRE(data.signalStrength == 519);
}
