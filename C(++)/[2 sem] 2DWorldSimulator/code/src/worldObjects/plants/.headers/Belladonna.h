//
// Created by szymo on 4/18/2023.
//

#ifndef DEV_BELLADONNA_H
#define DEV_BELLADONNA_H

#include "../../.headers/Plant.h"

class Belladonna : public Plant {
public:
    Belladonna(int x, int y, World* world);

    ~Belladonna() override;

    Organism* collision(Organism* attacker);

    std::string getSpecieName() const override;
};


#endif //DEV_BELLADONNA_H
