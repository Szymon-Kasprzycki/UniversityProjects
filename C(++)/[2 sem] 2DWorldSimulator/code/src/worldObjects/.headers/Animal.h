//
// Created by szymo on 4/10/2023.
//

#ifndef DEV_ANIMAL_H
#define DEV_ANIMAL_H

#include "Organism.h"
#include "../../.headers/World.h"

using namespace std;

class Animal: public Organism {
protected:
    World *world;
public:
    Animal(int x, int y, World *world, int strength, int initiative, char symbol, int age = 0);

    void action() override;

    Organism * collision(Organism *attacker) override;

    void move(int x, int y);

    void multiply(int x, int y);

    virtual bool isWolf();

    virtual bool isSheep();

    virtual bool isFox();

    virtual bool isAntelope();

    std::string getSpecieName() const override;

    ~Animal() override;
};


#endif //DEV_ANIMAL_H
