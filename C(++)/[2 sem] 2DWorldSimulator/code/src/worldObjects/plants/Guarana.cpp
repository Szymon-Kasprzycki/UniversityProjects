//
// Created by szymo on 4/18/2023.
//

#include ".headers/Guarana.h"

#define GUARANA_STRENGTH 0
#define GUARANA_INITIATIVE 0
#define GUARANA_SYMBOL '^'

Guarana::Guarana(int x, int y, World *world) : Plant(x, y, world, GUARANA_STRENGTH, GUARANA_INITIATIVE, GUARANA_SYMBOL) {}

Guarana::~Guarana() = default;

Organism* Guarana::collision(Organism *attacker) {
    attacker->setStrength(attacker->getStrength() + 3);
    return attacker;
}

std::string Guarana::getSpecieName() const {
    return "Guarana";
}