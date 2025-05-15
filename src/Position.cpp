#include "Position.hpp"
#include <string>
#include <stdexcept>

Position::Position(int x, int y) {
    setX(x);
    setY(y);
}

int Position::getX() const {
    return m_x;
}

void Position::setX(int x) {
    if (x < 0) {
        throw std::invalid_argument("X coordinate cannot be negative");
    }
    m_x = x;
}

int Position::getY() const {
    return m_y;
}

void Position::setY(int y) {
    if (y < 0) {
        throw std::invalid_argument("Y coordinate cannot be negative");
    }
    m_y = y;
}

std::string Position::toString() {
    return "(" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")";
}

double Position::distance(Position position) const {
    double dx = static_cast<double>(getX()) - static_cast<double>(position.getX());
    double dy = static_cast<double>(getY()) - static_cast<double>(position.getY());
    return std::sqrt((dx * dx) + (dy * dy));
}

void Position::move(int dx, int dy) {
    setX(getX() + dx);
    setY(getY() + dy);
}