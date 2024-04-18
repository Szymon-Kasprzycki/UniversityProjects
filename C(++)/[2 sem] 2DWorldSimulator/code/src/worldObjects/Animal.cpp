//
// Created by szymo on 4/10/2023.
//

#include <iostream>
#include ".headers/Animal.h"
#include ".headers/Organism.h"
#include "../utils/helpFuncs.h"
#include "animals/.headers/Wolf.h"
#include "animals/.headers/Sheep.h"
#include "animals/.headers/Fox.h"
#include "animals/.headers/Turtle.h"
#include "animals/.headers/Antelope.h"

using namespace std;

Animal::Animal(int x, int y, World *world, int strength, int initiative, char symbol, int age) : Organism(x, y, strength, initiative, symbol, age) {
    this->world = world;
    this->type = "Animal";
}

void Animal::move(int x, int y) {
    this->world->moveOrganism(this, x, y);
}

void Animal::action() {
    int step;

    // Antelope has a chance to move twice as far
    if (this->symbol == 'A') step = 2;
    else step = 1;

    int newX = this->x;
    int newY = this->y;
    int direction = random(0, 3);
    switch (direction) {
        case 0:
            newX += step;
            break;
        case 1:
            newX -= step;
            break;
        case 2:
            newY += step;
            break;
        case 3:
            newY -= step;
            break;
        default:
            break;
    }
    if (isOnMap(newX, newY, this->world->getWidth(), this->world->getHeight())) {
        this->world->makeMove(this, newX, newY);
    }
    else { this->action(); }
}

// Function checks collision and returns pointer to the winner or nullptr if organisms multiply
// When used, the pointer returned by this function should be used to set the pointer in the world to the winner
Organism *Animal::collision(Organism *attacker) {
    if (attacker->getType() == "Animal" && this->getSymbol() == attacker->getSymbol())
    {
        if (attacker->getAge() < 3 || this->getAge() < 3) { return nullptr; }
        this->multiply(this->x, this->y);
        return nullptr;
    }
    else if (attacker->getStrength() < this->strength) { return this; }
    else { return attacker; }
}

void Animal::multiply(int x, int y) {
    int babyX = x;
    int babyY = y;
    // get random nearby position
    this->world->findFreeNeighbourCell(x, y, babyX, babyY);

    Organism *baby;
    switch (symbol) {
        case 'W':
            baby = new Wolf(babyX, babyY, this->world);
            break;
        case 'S':
            baby = new Sheep(babyX, babyY, this->world);
            break;
        case 'F':
            baby = new Fox(babyX, babyY, this->world);
            break;
        case 'T':
            baby = new Turtle(babyX, babyY, this->world);
            break;
        case 'A':
            baby = new Antelope(babyX, babyY, this->world);
            break;
        default:
            baby = new Animal(babyX, babyY, this->world, this->strength, this->initiative, this->symbol);
            break;
    }
    this->world->MakeComment(this->getSpecieName() + " multiplied!");
    this->world->addOrganism(baby);
}

bool Animal::isWolf() { return false; }

bool Animal::isSheep() { return false; }

bool Animal::isFox() { return false; }

bool Animal::isAntelope() { return false; }

std::string Animal::getSpecieName() const { return "Animal"; }

Animal::~Animal() = default;