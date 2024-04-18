//
// Created by szymo on 4/18/2023.
//

#include ".headers/Antelope.h"
#include "../../utils/helpFuncs.h"
#include "iostream"

using namespace std;

#define ANTELOPE_STRENGTH 4
#define ANTELOPE_INITIATIVE 4
#define ANTELOPE_SYMBOL 'A'
#define CHANCE_OF_ESCAPE 50

Antelope::Antelope(int x, int y, World *world) : Animal(x, y, world, ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, ANTELOPE_SYMBOL) {}

Antelope::~Antelope() = default;

Organism* Antelope::collision(Organism *attacker) {
    cout << "Antelope collision!!";
    int chance = random(0, 100);
    if (chance <= CHANCE_OF_ESCAPE)
    {
        int moveX;
        int moveY;
        this->world->findFreeNeighbourCell(this->getX(), this->getY(), moveX, moveY);
        if (moveX != -1 && moveY != -1) this->world->moveOrganism(this, moveX, moveY);
        // return attacker but does not remove antelope
        return nullptr;
    }
    else {
        return Animal::collision(attacker);
    }
}

bool Antelope::isAntelope() {
    return true;
}

string Antelope::getSpecieName() const {
    return "Antelope";
}