//
// Created by szymo on 4/18/2023.
//

#ifndef DEV_SOSNOWSKYHOGWEED_H
#define DEV_SOSNOWSKYHOGWEED_H


#include "../../.headers/Plant.h"

class SosnowskyHogweed : public Plant {
public:
    SosnowskyHogweed(int x, int y, World* world);

    ~SosnowskyHogweed() override;

    Organism* collision(Organism* attacker) override;

    void action() override;

    std::string getSpecieName() const override;
};


#endif //DEV_SOSNOWSKYHOGWEED_H
