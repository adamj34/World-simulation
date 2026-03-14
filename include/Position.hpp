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

        bool operator==(const Position& other) const;

        int getX() const;
        void setX(int x);
        int getY() const;
        void setY(int y);

        std::string toString() const;
        
        void move(int dx, int dy);
};