//
// Created by szymo on 4/18/2023.
//

#include ".headers/SosnowskyHogweed.h"
#include "../../utils/helpFuncs.h"

#define SOSNOWSKY_HOGWEED_STRENGTH 10
#define SOSNOWSKY_HOGWEED_INITIATIVE 0
#define SOSNOWSKY_HOGWEED_SYMBOL '$'

SosnowskyHogweed::SosnowskyHogweed(int x, int y, World *world) : Plant(x, y, world, SOSNOWSKY_HOGWEED_STRENGTH,
                                                                       SOSNOWSKY_HOGWEED_INITIATIVE,
                                                                       SOSNOWSKY_HOGWEED_SYMBOL)
{
    this->spreadChance = 3; // 3% chance to spread
}

SosnowskyHogweed::~SosnowskyHogweed() = default;

Organism *SosnowskyHogweed::collision(Organism *attacker)
{
    return this;
}

void SosnowskyHogweed::action() {
    int x[4] = {this->getX() - 1, this->getX() + 1, this->getX(), this->getX()};
    int y[4] = {this->getY(), this->getY(), this->getY() + 1, this->getY() - 1};

    for (int i = 0; i < 4; i++) {
        if (!isOnMap(x[i], y[i], this->world->getWidth(), this->world->getHeight())) continue;
        Organism* occupant = this->world->getOrganism(x[i], y[i]);
        if (occupant != nullptr && occupant->getType() != "Plant") {
            this->world->MakeComment(this->getSpecieName() + " killed " + occupant->getSpecieName());
            this->world->removeOrganism(x[i], y[i]);
        }
    }

    // Spreading chance
    Plant::action();
}

std::string SosnowskyHogweed::getSpecieName() const {
    return "SosnowskyHogweed";
}