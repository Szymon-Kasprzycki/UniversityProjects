//
// Created by szymo on 4/16/2023.
//

#ifndef DEV_GRASS_H
#define DEV_GRASS_H


#include "../../.headers/Plant.h"

class Grass : public Plant {
public:
    Grass(int x, int y, World *world);

    ~Grass() override;

    std::string getSpecieName() const override;
};


#endif //DEV_GRASS_H
