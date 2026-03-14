#pragma once

enum class SpeciesCodes {
    Unknown,
    Animal,
    Plant,
    Wolf,
    Sheep,
    Grass,
    Dandelion,
    Toadstool
};

constexpr std::string speciesCodeToSymbol(SpeciesCodes code) {
    switch (code) {
        case SpeciesCodes::Animal:
            return "A";
        case SpeciesCodes::Plant:
            return "P";
        case SpeciesCodes::Wolf:
            return "W";
        case SpeciesCodes::Sheep:
            return "S";
        case SpeciesCodes::Grass:
            return "G";
        case SpeciesCodes::Dandelion:
            return "D";
        case SpeciesCodes::Toadstool:
            return "T";
        case SpeciesCodes::Unknown:
        default:
            return "O";
    }
}

namespace species_defaults {

struct Stats {
    int power;
    int initiative;
    int liveLength;
    int powerToReproduce;
};

constexpr Stats wolf{
    .power = 8,
    .initiative = 5,
    .liveLength = 20,
    .powerToReproduce = 16,
};

constexpr Stats sheep{
    .power = 3,
    .initiative = 3,
    .liveLength = 10,
    .powerToReproduce = 6,
};

constexpr Stats grass{
    .power = 0,
    .initiative = 0,
    .liveLength = 6,
    .powerToReproduce = 3,
};

constexpr Stats dandelion{
    .power = 0,
    .initiative = 0,
    .liveLength = 6,
    .powerToReproduce = 2,
};

constexpr Stats toadstool{
    .power = 0,
    .initiative = 0,
    .liveLength = 12,
    .powerToReproduce = 4,
};

} // namespace species_defaults