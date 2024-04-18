//
// Created by szymo on 4/18/2023.
//

#ifndef DEV_SOWTHISTLE_H
#define DEV_SOWTHISTLE_H

#include "../../.headers/Plant.h"


class SowThistle : public Plant {
public:
    SowThistle(int x, int y, World *world);

    ~SowThistle() override;

    void action() override;

    std::string getSpecieName() const override;
};


#endif //DEV_SOWTHISTLE_H
