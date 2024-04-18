//
// Created by szymo on 4/18/2023.
//

#include ".headers/Belladonna.h"

#define BELLADONNA_STRENGTH 99
#define BELLADONNA_INITIATIVE 0
#define BELLADONNA_SYMBOL '@'

Belladonna::Belladonna(int x, int y, World *world) : Plant(x, y, world, BELLADONNA_STRENGTH, BELLADONNA_INITIATIVE, BELLADONNA_SYMBOL)
{
    this->spreadChance = 2; // 2% chance to spread
}

Belladonna::~Belladonna() = default;

Organism* Belladonna::collision(Organism *attacker) {
    this->world->MakeComment("Belladonna killed " + attacker->getSpecieName());
    return this;
}

std::string Belladonna::getSpecieName() const {
    return "Belladonna";
}