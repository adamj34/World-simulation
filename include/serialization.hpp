#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <fstream>
#include <memory>
#include <string>

#include "Position.hpp"
#include "World.hpp"
#include "organisms/Animal.hpp"
#include "organisms/LineageInfo.hpp"
#include "organisms/Organism.hpp"
#include "organisms/Plant.hpp"

#include "organisms/Dandelion.hpp"
#include "organisms/Grass.hpp"
#include "organisms/Sheep.hpp"
#include "organisms/Toadstool.hpp"
#include "organisms/Wolf.hpp"

// Make Position, Organism, and World "split-free" so we can define separate save() and load()
BOOST_SERIALIZATION_SPLIT_FREE(Position)
BOOST_SERIALIZATION_SPLIT_FREE(LineageInfo)
BOOST_SERIALIZATION_SPLIT_FREE(World)
BOOST_SERIALIZATION_SPLIT_FREE(Organism)
BOOST_SERIALIZATION_SPLIT_FREE(Animal)
BOOST_SERIALIZATION_SPLIT_FREE(Plant)
BOOST_SERIALIZATION_SPLIT_FREE(Grass)
BOOST_SERIALIZATION_SPLIT_FREE(Sheep)
BOOST_SERIALIZATION_SPLIT_FREE(Wolf)
BOOST_SERIALIZATION_SPLIT_FREE(Toadstool)
BOOST_SERIALIZATION_SPLIT_FREE(Dandelion)

namespace boost {
namespace serialization {

// Serialization for Position
template <class Archive>
void save(Archive& ar, const Position& pos, const unsigned int version) {
    int x{ pos.getX() };
    int y{ pos.getY() };
    ar & x & y;
}

template <class Archive>
void load(Archive& ar, Position& pos, const unsigned int version) {
    int x{ 0 };
    int y{ 0 };
    ar & x & y;
    pos.setX(x);
    pos.setY(y);
}

// Serialization for LineageInfo
template <class Archive>
void save(Archive& ar, const LineageInfo& lineage, const unsigned int version) {
    int birthTurn{ lineage.birthTurn };
    int deathTurn{ lineage.deathTurn };
    std::shared_ptr<Organism> parent = lineage.parent;

    ar & birthTurn & deathTurn & parent;
}

template <class Archive>
void load(Archive& ar, LineageInfo& lineage, const unsigned int version) {
    int birthTurn{ -1 };
    int deathTurn{ -1 };
    std::shared_ptr<Organism> parent{ nullptr };

    ar & birthTurn & deathTurn & parent;

    lineage.birthTurn = birthTurn;
    lineage.deathTurn = deathTurn;
    lineage.parent = parent;
}

// Serialization for Organism
template <class Archive>
void save(Archive& ar, const Organism& o, const unsigned int version) {
    int power{ o.getPower() };
    std::string species{ o.getSpecies() };
    int initiative { o.getInitiative() };
    int liveLength { o.getLiveLength() };
    int powerToReproduce { o.getPowerToReproduce() };
    Position position { o.getPosition() };
    LineageInfo lineageInfo { o.getLineageInfo() };

    ar & power & species & initiative & liveLength & powerToReproduce & position & lineageInfo;
}

template <class Archive>
void load(Archive& ar, Organism& o, const unsigned int version) {
    int power{ 0 };
    std::string species{};
    int initiative{ 0 };
    int liveLength{ 0 };
    int powerToReproduce{ 0 };
    Position position{ 0, 0 };
    LineageInfo lineageInfo{};

    ar & power & species & initiative & liveLength & powerToReproduce & position & lineageInfo;

    o.setPower(power);
    o.setSpecies(species);
    o.setInitiative(initiative);
    o.setLiveLength(liveLength);
    o.setPowerToReproduce(powerToReproduce);
    o.setPosition(position);
    o.setLineageInfo(lineageInfo);
}

// Serialization for Animal
template <class Archive>
void save(Archive& ar, const Animal& a, const unsigned int version) {
    ar& boost::serialization::base_object<Organism>(a);
}

template <class Archive>
void load(Archive& ar, Animal& a, const unsigned int version) {
    ar& boost::serialization::base_object<Organism>(a);
}

// Serialization for Plant
template <class Archive>
void save(Archive& ar, const Plant& p, const unsigned int version) {
    ar& boost::serialization::base_object<Organism>(p);
}
template <class Archive>
void load(Archive& ar, Plant& p, const unsigned int version) {
    ar& boost::serialization::base_object<Organism>(p);
}

// Serialization for Grass
template <class Archive>
void save(Archive& ar, const Grass& g, const unsigned int version) {
    ar& boost::serialization::base_object<Plant>(g);
}
template <class Archive>
void load(Archive& ar, Grass& g, const unsigned int version) {
    ar& boost::serialization::base_object<Plant>(g);
}
// Serialization for Sheep
template <class Archive>
void save(Archive& ar, const Sheep& s, const unsigned int version) {
    ar& boost::serialization::base_object<Animal>(s);
}
template <class Archive>
void load(Archive& ar, Sheep& s, const unsigned int version) {
    ar& boost::serialization::base_object<Animal>(s);
}
// Serialization for Wolf
template <class Archive>
void save(Archive& ar, const Wolf& w, const unsigned int version) {
    ar& boost::serialization::base_object<Animal>(w);
}
template <class Archive>
void load(Archive& ar, Wolf& w, const unsigned int version) {
    ar& boost::serialization::base_object<Animal>(w);
}
// Serialization for Toadstool
template <class Archive>
void save(Archive& ar, const Toadstool& t, const unsigned int version) {
    ar& boost::serialization::base_object<Plant>(t);
}
template <class Archive>
void load(Archive& ar, Toadstool& t, const unsigned int version) {
    ar& boost::serialization::base_object<Plant>(t);
}
// Serialization for Dandelion
template <class Archive>
void save(Archive& ar, const Dandelion& d, const unsigned int version) {
    ar& boost::serialization::base_object<Plant>(d);
}
template <class Archive>
void load(Archive& ar, Dandelion& d, const unsigned int version) {
    ar& boost::serialization::base_object<Plant>(d);
}

// Serialization for World
template <class Archive>
void save(Archive& ar, const World& w, const unsigned int version) {
    int wx{ w.getWorldX() };
    int wy{ w.getWorldY() };
    int startWorldX{ w.getStartWorldX() };
    int startWorldY{ w.getStartWorldY() };
    std::vector<std::shared_ptr<Organism>> orgs{ w.getOrganisms() };

    ar & wx & wy & startWorldX & startWorldY & orgs;
}

template <class Archive>
void load(Archive& ar, World& w, const unsigned int version) {
    int wx{ 0 };
    int wy{ 0 };
    int startWorldX{ 0 };
    int startWorldY{ 0 };
    std::vector<std::shared_ptr<Organism>> orgs{};

    ar & wx & wy & startWorldX & startWorldY & orgs;

    w.setWorldX(wx);
    w.setWorldY(wy);
    w.setStartWorldX(startWorldX);
    w.setStartWorldY(startWorldY);
    w.setOrganisms(orgs);
}

// Save and load functions for World
void saveWorld(const World& w, const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }
    boost::archive::text_oarchive oa(ofs);
    oa << w;
}

void loadWorld(World& w, const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Could not open file for reading: " + filename);
    }
    boost::archive::text_iarchive ia(ifs);
    ia >> w;
}

} // namespace serialization
} // namespace boost

BOOST_CLASS_EXPORT(Organism)
BOOST_CLASS_EXPORT(Animal)
BOOST_CLASS_EXPORT(Plant)
BOOST_CLASS_EXPORT(Grass)
BOOST_CLASS_EXPORT(Sheep)
BOOST_CLASS_EXPORT(Toadstool)
BOOST_CLASS_EXPORT(Dandelion)
BOOST_CLASS_EXPORT(Wolf)