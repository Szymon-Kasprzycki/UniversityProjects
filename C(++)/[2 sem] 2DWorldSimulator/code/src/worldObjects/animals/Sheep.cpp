//
// Created by szymo on 4/16/2023.
//

#include ".headers/Sheep.h"

#define SHEEP_STRENGTH 4
#define SHEEP_INITIATIVE 4
#define SHEEP_SYMBOL 'S'

Sheep::Sheep(int x, int y, World *world) : Animal(x, y, world, SHEEP_STRENGTH, SHEEP_INITIATIVE, SHEEP_SYMBOL)
{}

bool Sheep::isSheep() { return true; }

std::string Sheep::getSpecieName() const { return "Sheep"; }