//
// Created by szymo on 4/10/2023.
//

#ifndef DEV_PLANT_H
#define DEV_PLANT_H

#include "Organism.h"
#include "../../.headers/World.h"


class Plant : public Organism {
protected:
    World *world;
    int spreadChance;
public:
    Plant(int x, int y, World *world, int strength, int initiative, char symbol, int age = 0);

    void action() override;

    void multiply(int x, int y);

    Organism * collision(Organism *attacker) override;
};


#endif //DEV_PLANT_H
