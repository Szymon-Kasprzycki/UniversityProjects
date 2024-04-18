//
// Created by szymo on 4/15/2023.
//

#ifndef DEV_HUMAN_H
#define DEV_HUMAN_H


#include "Animal.h"

class Human : public Animal {
private:
    int powerCounter;
    int powerCooldownCounter;
    bool isPowerActive;
    bool isPowerOnCooldown;
    bool endGame = false;
    void powerTick();
    void powerCooldownTick();
    void powerDurationTick();
    void usePower();
    void EndGame();
public:
    Human(int x, int y, World *world);

    void action() override;

    bool isEndGame() const;

    void death() override;

    std::string getSpecieName() const override;

    void saveToFile(std::ostream &file);

    void setPowerActive(bool isPowerActive);

    void setPowerOnCooldown(bool isPowerOnCooldown);

    void setPowerCounter(int powerCounter);

    void setPowerCooldownCounter(int powerCooldownCounter);

    void setEndGame(bool endGame);
};


#endif //DEV_HUMAN_H
