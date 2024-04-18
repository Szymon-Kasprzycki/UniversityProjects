//
// Created by szymo on 4/18/2023.
//

#include ".headers/SowThistle.h"

#define SOW_INITIATIVE 0
#define SOW_STRENGTH 0
#define SOW_SYMBOL '&'

SowThistle::SowThistle(int x, int y, World *world) : Plant(x, y, world, SOW_STRENGTH, SOW_INITIATIVE, SOW_SYMBOL) {}

SowThistle::~SowThistle() = default;

void SowThistle::action()
{
    for (int i = 0; i<3; i++) { Plant::action(); }
}

std::string SowThistle::getSpecieName() const
{
    return "SowThistle";
}