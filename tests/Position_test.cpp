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

    SECTION("Move with zero deltas") {
        Position pos(5, 7);
        pos.move(0, 0);
        REQUIRE(pos.getX() == 5);
        REQUIRE(pos.getY() == 7);
    }

    SECTION("Move to origin") {
        Position pos(3, 4);
        pos.move(-3, -4);
        REQUIRE(pos.getX() == 0);
        REQUIRE(pos.getY() == 0);
    }
}

TEST_CASE("Position constructors", "[Position]") {
    SECTION("Default constructor initializes to (0, 0)") {
        Position pos{};
        REQUIRE(pos.getX() == 0);
        REQUIRE(pos.getY() == 0);
    }

    SECTION("Parameterized constructor with valid positive values") {
        Position pos(10, 15);
        REQUIRE(pos.getX() == 10);
        REQUIRE(pos.getY() == 15);
    }

    SECTION("Parameterized constructor with zero values") {
        Position pos(0, 0);
        REQUIRE(pos.getX() == 0);
        REQUIRE(pos.getY() == 0);
    }

    SECTION("Parameterized constructor with large values") {
        Position pos(1000, 2000);
        REQUIRE(pos.getX() == 1000);
        REQUIRE(pos.getY() == 2000);
    }
}

TEST_CASE("Position equality operator", "[Position]") {
    SECTION("Two positions with same coordinates are equal") {
        Position pos1(5, 7);
        Position pos2(5, 7);
        REQUIRE(pos1 == pos2);
    }

    SECTION("Two positions with different X are not equal") {
        Position pos1(5, 7);
        Position pos2(6, 7);
        REQUIRE(!(pos1 == pos2));
    }

    SECTION("Two positions with different Y are not equal") {
        Position pos1(5, 7);
        Position pos2(5, 8);
        REQUIRE(!(pos1 == pos2));
    }

    SECTION("Two positions at origin are equal") {
        Position pos1{};
        Position pos2{};
        REQUIRE(pos1 == pos2);
    }

    SECTION("Position at origin equals explicitly set zero position") {
        Position pos1{};
        Position pos2(0, 0);
        REQUIRE(pos1 == pos2);
    }
}

TEST_CASE("Position toString", "[Position]") {
    SECTION("toString returns correct format") {
        Position pos(5, 7);
        REQUIRE(pos.toString() == "(5, 7)");
    }

    SECTION("toString at origin") {
        Position pos{};
        REQUIRE(pos.toString() == "(0, 0)");
    }

    SECTION("toString with large values") {
        Position pos(100, 250);
        REQUIRE(pos.toString() == "(100, 250)");
    }
}