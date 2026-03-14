#pragma once

#include "Lineage.hpp"
#include "Position.hpp"
#include <string>
#include <memory>
#include <vector>

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
        std::string m_species{ "O" };
        std::string m_subspecies{ "O" };
        Position m_position{ 0, 0 };
        LineageInfo m_lineageInfo{};

    public:
        Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Organism(int power, Position position);
        explicit Organism(Position position);
        Organism() = default;

        Organism(const Organism&) = default;

        Organism& operator=(const Organism&) = default;

        bool operator==(const Organism& other) const;

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

        LineageInfo getLineageInfo() const;
        void setLineageInfo(LineageInfo lineageInfo);

        std::shared_ptr<Organism> getParent() const;

        std::string getSpecies() const;
        void setSpecies(std::string spec);

        std::string getSubspecies() const;
        void setSubspecies(std::string subspec);

        bool canReproduce() const;

        bool isAlive() const;

        void setDeathTurn(int deathTurn);

        std::vector<std::shared_ptr<Organism>> getAncestorHistory() const;

        void printAncestorHistory() const;

        std::string toString() const;
        
        virtual void move(const Position& newPosition) = 0;
        virtual std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) = 0;
        virtual std::optional<std::shared_ptr<Organism>> reproduce() = 0;
        virtual std::shared_ptr<Organism> clone() = 0;
    };