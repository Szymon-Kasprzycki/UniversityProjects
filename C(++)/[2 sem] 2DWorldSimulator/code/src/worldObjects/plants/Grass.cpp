//
// Created by szymo on 4/16/2023.
//

#include ".headers/Grass.h"

#define GRASS_STRENGTH 0
#define GRASS_INITIATIVE 0
#define GRASS_SYMBOL '*'

Grass::Grass(int x, int y, World *world) : Plant(x, y, world, GRASS_STRENGTH, GRASS_INITIATIVE, GRASS_SYMBOL) {}

Grass::~Grass() = default;

std::string Grass::getSpecieName() const {
    return "Grass";
}