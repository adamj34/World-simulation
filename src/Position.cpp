#include "Position.hpp"
#include "validators.hpp"
#include <string>

Position::Position(int x, int y)
    : m_x{ x }
    , m_y{ y } {
    validators::validateValueNotNegative(x, "X coordinate");
    validators::validateValueNotNegative(y, "Y coordinate");
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

std::string Position::toString() {
    return "(" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")";
}

double Position::distance(const Position& position) const {
    double dx = static_cast<double>(this->getX()) - static_cast<double>(position.getX());
    double dy = static_cast<double>(this->getY()) - static_cast<double>(position.getY());
    return std::sqrt((dx * dx) + (dy * dy));
}

void Position::move(int dx, int dy) {
    setX(getX() + dx);
    setY(getY() + dy);
}