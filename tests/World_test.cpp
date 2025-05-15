#include <catch2/catch_test_macros.hpp>
#include "World.hpp"

TEST_CASE("Negative values for world dimensions are not allowed", "[World]") {
    SECTION("Negative X dimension throws invalid_argument when constructing World") {
        REQUIRE_THROWS_AS(World(-1, 5), std::invalid_argument);
    }
    
    SECTION("Negative Y dimension throws invalid_argument when constructing World") {
        REQUIRE_THROWS_AS(World(5, -1), std::invalid_argument);
    }

    SECTION("Negative X dimension throws invalid_argument when setting World X") {
        World world {};
        REQUIRE_THROWS_AS(world.setWorldX(-1), std::invalid_argument);
    }

    SECTION("Negative Y dimension throws invalid_argument when setting World Y") {
        World world {};
        REQUIRE_THROWS_AS(world.setWorldY(-1), std::invalid_argument);
    }
}