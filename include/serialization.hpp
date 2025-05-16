//// filepath: /home/todd/cpp/1-world-adamj34/include/serialization.hpp
#pragma once

#include <boost/serialization/split_free.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <fstream>
#include <string>

#include "World.hpp"
#include "Position.hpp"
#include "organisms/Organism.hpp"

// Make Position, Organism, and World "split-free" so we can define separate save() and load() 
BOOST_SERIALIZATION_SPLIT_FREE(Position)
BOOST_SERIALIZATION_SPLIT_FREE(Organism)
BOOST_SERIALIZATION_SPLIT_FREE(World)

namespace boost {
namespace serialization {

// Serialization for Position
template <class Archive>
void save(Archive& ar, const Position& pos, const unsigned int version)
{
    int x { pos.getX() };
    int y { pos.getY() };
    ar & x & y;
}

template <class Archive>
void load(Archive& ar, Position& pos, const unsigned int version)
{
    int x {0};
    int y {0};
    ar & x & y;
    pos.setX(x);
    pos.setY(y);
}

// Serialization for Organism
template <class Archive>
void save(Archive& ar, const Organism& o, const unsigned int version)
{
    // Example for a simple set of fields
    int power { o.getPower() };
    std::string species = o.getSpecies();
    int initiative = o.getInitiative();
    int liveLength = o.getLiveLength();
    int powerToReproduce = o.getPowerToReproduce();
    Position position = o.getPosition();

    ar & power 
       & species
       & initiative
       & liveLength
       & powerToReproduce
       & position;
}

template <class Archive>
void load(Archive& ar, Organism& o, const unsigned int version)
{
    int power {0};
    std::string species {};
    int initiative {0};
    int liveLength {0};
    int powerToReproduce {0};
    Position position {0, 0};

    ar & power 
       & species
       & initiative
       & liveLength
       & powerToReproduce
       & position;

    o.setPower(power);
    o.setSpecies(species);
    o.setInitiative(initiative);
    o.setLiveLength(liveLength);
    o.setPowerToReproduce(powerToReproduce);
    o.setPosition(position);
}

// Serialization for World
template <class Archive>
void save(Archive& ar, const World& w, const unsigned int version)
{
    int wx = w.getWorldX();
    int wy = w.getWorldY();
    int turn = w.getTurn();
    int startWorldX = w.getStartWorldX();
    int startWorldY = w.getStartWorldY();

    // Example for storing a copy of organisms
    std::vector<Organism> orgs = w.getOrganisms();

    ar & wx & wy & turn & startWorldX & startWorldY & orgs;
}

template <class Archive>
void load(Archive& ar, World& w, const unsigned int version)
{
    int wx, wy, turn, startWorldX, startWorldY {0};
    std::vector<Organism> orgs {};

    ar & wx & wy & turn & startWorldX & startWorldY & orgs;

    w.setWorldX(wx);
    w.setWorldY(wy);
    w.setTurn(turn);
    w.setStartWorldX(startWorldX);
    w.setStartWorldY(startWorldY);
    w.setOrganisms(orgs);
}


// Split-free serialization for Position, Organism, and World
template <class Archive>
inline void serialize(Archive& ar, Position& pos, const unsigned int version)
{
    split_free(ar, pos, version);
}

template <class Archive>
inline void serialize(Archive& ar, Organism& o, const unsigned int version)
{
    split_free(ar, o, version);
}

template <class Archive>
inline void serialize(Archive& ar, World& w, const unsigned int version)
{
    split_free(ar, w, version);
}


// Save and load functions for World
inline void saveWorld(const World& w, const std::string& filename)
{
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << w;
}

inline void loadWorld(World& w, const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Could not open file for reading: " + filename);
    }
    boost::archive::text_iarchive ia(ifs);
    ia >> w;
}

} // namespace boost
} // namespace serialization