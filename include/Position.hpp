#pragma once

#include <cmath>
#include <string>

class Position {
    private:
        int m_x{ 0 };
        int m_y{ 0 };

    public:
        Position(int x, int y);
        Position() = default;

        // Compiler-generated copy constructor will be like:
        // Position(const Position& other) : m_x(other.m_x), m_y(other.m_y) {}

        // Compiler-generated copy assignment operator will be like:
        // Position& operator=(const Position& other) {
        //     if (this != &other) {
        //         m_x = other.m_x;
        //         m_y = other.m_y;
        //     }
        //     return *this;
        // }

        int getX() const;
        void setX(int x);
        int getY() const;
        void setY(int y);

        std::string toString();

        double distance(Position position) const;
        void move(int dx, int dy);
};