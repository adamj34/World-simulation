#include "Position.hpp"
#include "validators.hpp"
#include <string>

Position::Position(int x, int y)
    : m_x{ x }
    , m_y{ y } {
    validators::validateValueNotNegative(x, "X coordinate");
    validators::validateValueNotNegative(y, "Y coordinate");
}

bool Position::operator==(const Position& other) const {
    return m_x == other.m_x && m_y == other.m_y;
}

int Position::getX() const {
    return m_x;
}

void Position::setX(int x) {
    validators::validateValueNotNegative(x, "X coordinate");
    m_x = x;
}

int Position::getY() const {
    return m_y;
}

void Position::setY(int y) {
    validators::validateValueNotNegative(y, "Y coordinate");
    m_y = y;
}

void Position::move(int dx, int dy) {
    int targetX = getX() + dx;
    int targetY = getY() + dy;

    validators::validateValueNotNegative(targetX, "X coordinate");
    validators::validateValueNotNegative(targetY, "Y coordinate");

    m_x = targetX;
    m_y = targetY;
}

std::string Position::toString() const {
    return "(" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")";
}