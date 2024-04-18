//
// Created by szymo on 4/16/2023.
//

#include ".headers/Fox.h"
#include "../../utils/helpFuncs.h"

#define FOX_STRENGTH 3
#define FOX_INITIATIVE 7
#define FOX_SYMBOL 'F'

Fox::Fox(int x, int y, World *world) : Animal(x, y, world, FOX_STRENGTH, FOX_INITIATIVE, FOX_SYMBOL)
{}

bool Fox::isFox() {
    return true;
}

void Fox::action() {
    int newX = this->getX();
    int newY = this->getY();
    Organism* occupant;
    int tries = 0;
    do {
        int direction = random(0, 3);
        switch (direction) {
            case 0:
                newX++;
                break;
            case 1:
                newX--;
                break;
            case 2:
                newY++;
                break;
            case 3:
                newY--;
                break;
        }
        if (!isOnMap(newX, newY, this->world->getWidth(), this->world->getHeight())) {
            newX = this->getX();
            newY = this->getY();
            tries++;
            continue;
        }
        occupant = this->world->getOrganism(x, y);
        if (occupant == nullptr || occupant->getStrength() < this->getStrength() || occupant->getSymbol() == this->getSymbol()) { break; }
    } while(tries < 8);

    if (tries == 8) { return; }
    this->world->makeMove(this, newX, newY);
}

std::string Fox::getSpecieName() const {
    return "Fox";
}