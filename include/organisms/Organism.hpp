#pragma once
#include "Position.hpp"
#include <string>

/*
power: zwiększa się co jedną turę o 1; decyduje o sile organizmu
initiative: priorytet decyduje o kolejności wykonania ruchu w ramach jednej tury
position: położenie w świecie
liveLength: liczba tur do końca życia
powerToReproduce: granica dolna siły, powyżej której może się rozmnażać; po rozmnożeniu traci połowę siły
sign: znak reprezentujący organizm w świecie
*/

class Organism {
    private:
        int m_power{ 0 };
        int m_initiative{ 0 };
        int m_liveLength{ 0 };
        int m_powerToReproduce{ 0 };
        Position m_position{ 0, 0 };
        std::string m_species{ "O" };

    public:
        Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Organism(int power, Position position);
        explicit Organism(Position position);
        Organism() = default;

        // Copy constructor (Member-wise copy using copy constructors)
        Organism(const Organism&) = default;
        
        // Copy assignment operator (Member-wise assignment using operator=)
        Organism& operator=(const Organism&) = default;

        virtual ~Organism() = default;

        int getPower() const;
        void setPower(int power);

        int getInitiative() const;
        void setInitiative(int initiative);

        int getLiveLength() const;
        void setLiveLength(int liveLength);

        int getPowerToReproduce() const;
        void setPowerToReproduce(int powerToReproduce);

        Position getPosition() const;
        void setPosition(Position position);

        std::string getSpecies() const;
        void setSpecies(std::string spec);

        // Test function to change x coordinate
        void test_change_x(int x);

        std::string toString() const;

        virtual void move(int dx, int dy);
};