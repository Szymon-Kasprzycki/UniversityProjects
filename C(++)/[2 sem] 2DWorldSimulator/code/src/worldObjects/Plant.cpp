//
// Created by szymo on 4/10/2023.
//

#include ".headers/Plant.h"
#include "../utils/helpFuncs.h"
#include "plants/.headers/Grass.h"
#include "plants/.headers/SosnowskyHogweed.h"
#include "plants/.headers/Guarana.h"
#include "plants/.headers/SowThistle.h"
#include "plants/.headers/Belladonna.h"

#define DEFAULT_CHANCE_OF_MULTIPLY 5

using namespace std;

Plant::Plant(int x, int y, World *world, int strength, int initiative, char symbol, int age) : Organism(x, y, strength, initiative, symbol, age) {
    this->type = "Plant";
    this->world = world;
    this->spreadChance = DEFAULT_CHANCE_OF_MULTIPLY;
}

void Plant::action() {
    if (random(0, 100) <= this->spreadChance) { this->multiply(this->x, this->y); }
}

void Plant::multiply(int x, int y) {
    int babyX = x;
    int babyY = y;
    // get random nearby position
    this->world->findFreeNeighbourCell(x, y, babyX, babyY);
    // if there is no free cell in the neighbourhood, return
    if (babyX == -1 || babyY == -1) { return; }
    // create a new plant of the same type
    Organism* baby = nullptr;
    switch (this->symbol)
    {
        case '*':
            baby = new Grass(babyX, babyY, this->world);
            break;
        case '$':
            baby = new SosnowskyHogweed(babyX, babyY, this->world);
            break;
        case '^':
            baby = new Guarana(babyX, babyY, this->world);
            break;
        case '&':
            baby = new SowThistle(babyX, babyY, this->world);
            break;
        case '@':
            baby = new Belladonna(babyX, babyY, this->world);
        default:
            break;
    }
    this->world->addOrganism(baby);
}

Organism *Plant::collision(Organism *attacker) {
    if (attacker->getType() == "Animal" || attacker->getType() == "Human") { return attacker; }
    else { return this; }
}