#include <catch2/catch_test_macros.hpp>
#include "Position.hpp"

TEST_CASE("Negative values for position coordinates are not allowed", "[Position]") {
    SECTION("Negative X coordinate throws invalid_argument when constructing Position") {
        REQUIRE_THROWS_AS(Position(-1, 5), std::invalid_argument);
    }
    
    SECTION("Negative Y coordinate throws invalid_argument when constructing Position") {
        REQUIRE_THROWS_AS(Position(5, -1), std::invalid_argument);
    }

    SECTION("Negative X coordinate throws invalid_argument when setting Position X") {
        Position position {};
        REQUIRE_THROWS_AS(position.setX(-4), std::invalid_argument);
    }

    SECTION("Negative Y coordinate throws invalid_argument when setting Position Y") {
        Position position {};
        REQUIRE_THROWS_AS(position.setY(-3), std::invalid_argument);
    }
}