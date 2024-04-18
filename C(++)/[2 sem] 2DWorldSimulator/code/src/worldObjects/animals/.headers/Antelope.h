//
// Created by szymo on 4/18/2023.
//

#ifndef DEV_ANTELOPE_H
#define DEV_ANTELOPE_H


#include "../../.headers/Animal.h"

class Antelope : public Animal{
public:
    Antelope(int x, int y, World* world);

    ~Antelope() override;

    Organism* collision(Organism* attacker) override;

    bool isAntelope() override;

    std::string getSpecieName() const override;
};


#endif //DEV_ANTELOPE_H
