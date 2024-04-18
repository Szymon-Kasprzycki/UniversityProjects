//
// Created by szymo on 4/16/2023.
//

#ifndef DEV_FOX_H
#define DEV_FOX_H


#include "../../.headers/Animal.h"

class Fox : public Animal{
public:
    Fox(int x, int y, World *world);

    bool isFox() override;

    void action() override;

    std::string getSpecieName() const override;
};


#endif //DEV_FOX_H
