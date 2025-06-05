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

TEST_CASE("Position move function", "[Position]") {
    SECTION("Move with positive deltas") {
        Position pos(5, 3);
        pos.move(2, 4);
        REQUIRE(pos.getX() == 7);
        REQUIRE(pos.getY() == 7);
    }

    SECTION("Move with negative deltas") {
        Position pos(10, 8);
        pos.move(-3, -2);
        REQUIRE(pos.getX() == 7);
        REQUIRE(pos.getY() == 6);
    }

    SECTION("Move that would result in negative coordinates throws exception") {
        Position pos(2, 3);
        REQUIRE_THROWS_AS(pos.move(-5, 1), std::invalid_argument);
        REQUIRE_THROWS_AS(pos.move(1, -5), std::invalid_argument);
        REQUIRE_THROWS_AS(pos.move(-3, -4), std::invalid_argument);
    }
}