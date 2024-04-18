//
// Created by szymo on 4/16/2023.
//

#ifndef DEV_WOLF_H
#define DEV_WOLF_H

#include "../../.headers/Animal.h"

class Wolf : public Animal {
public:
    Wolf(int x, int y, World *world);

    bool isWolf() override;

    std::string getSpecieName() const override;
};


#endif //DEV_WOLF_H
