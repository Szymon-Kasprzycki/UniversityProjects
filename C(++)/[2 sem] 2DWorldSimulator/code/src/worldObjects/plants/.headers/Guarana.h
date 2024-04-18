//
// Created by szymo on 4/18/2023.
//

#ifndef DEV_GUARANA_H
#define DEV_GUARANA_H

#include "../../.headers/Plant.h"

class Guarana : public Plant {
public:
    Guarana(int x, int y, World *world);

    ~Guarana() override;

    Organism* collision(Organism* attacker) override;

    std::string getSpecieName() const override;
};


#endif //DEV_GUARANA_H
