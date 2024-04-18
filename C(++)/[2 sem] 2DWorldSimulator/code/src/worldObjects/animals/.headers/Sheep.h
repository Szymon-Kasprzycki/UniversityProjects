//
// Created by szymo on 4/16/2023.
//

#ifndef DEV_SHEEP_H
#define DEV_SHEEP_H

#include "../../.headers/Animal.h"
#include "../../../.headers/World.h"

class Sheep : public Animal {
public:
    Sheep(int x, int y, World *world);

    bool isSheep() override;

    std::string getSpecieName() const override;
};


#endif //DEV_SHEEP_H
