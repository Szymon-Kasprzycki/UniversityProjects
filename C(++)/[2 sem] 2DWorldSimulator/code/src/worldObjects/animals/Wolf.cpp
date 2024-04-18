//
// Created by szymo on 4/16/2023.
//

#include ".headers/Wolf.h"

#define WOLF_STRENGTH 9
#define WOLF_INITIATIVE 5
#define WOLF_SYMBOL 'W'


Wolf::Wolf(int x, int y, World *world) : Animal(x, y, world, WOLF_STRENGTH, WOLF_INITIATIVE, WOLF_SYMBOL)
{}

bool Wolf::isWolf() {
    return true;
}

std::string Wolf::getSpecieName() const {
    return "Wolf";
}