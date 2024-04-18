//
// Created by szymo on 4/18/2023.
//

#ifndef DEV_TURTLE_H
#define DEV_TURTLE_H

#include "../../../.headers/World.h"
#include "../../.headers/Animal.h"

class Turtle : public Animal{
public:
    Turtle(int x, int y, World* world);

    ~Turtle();

    void action() override;

    Organism* collision(Organism* attacker) override;

    std::string getSpecieName() const override;
};


#endif //DEV_TURTLE_H
