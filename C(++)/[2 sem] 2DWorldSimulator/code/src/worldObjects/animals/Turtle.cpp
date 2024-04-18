//
// Created by szymo on 4/18/2023.
//

#include ".headers/Turtle.h"
#include "../../utils/helpFuncs.h"
#include "iostream"

#define TURTLE_STRENGTH 2
#define TURTLE_INITIATIVE 1
#define TURTLE_SYMBOL 'T'
#define STAY_CHANCE 75

Turtle::Turtle(int x, int y, World *world) : Animal(x, y, world, TURTLE_STRENGTH, TURTLE_INITIATIVE, TURTLE_SYMBOL){}

Turtle::~Turtle() = default;

void Turtle::action() {
    int stay = random(0,100);
    if (stay > STAY_CHANCE) { Animal::action(); }
}

Organism* Turtle::collision(Organism *attacker) {
    if (attacker->getType() == "Animal" && this->getSymbol() == attacker->getSymbol())
    {
        this->multiply(this->x, this->y);
        return nullptr;
    }
    if (attacker->getStrength() >= 5) {return attacker;}
    else {
        // attacker gets back to previous position, so there's no need to return + move it
        return nullptr;
    }
}

std::string Turtle::getSpecieName() const {
    return "Turtle";
}