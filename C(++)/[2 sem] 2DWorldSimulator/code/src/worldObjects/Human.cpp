//
// Created by szymo on 4/15/2023.
//

#include ".headers/Human.h"
#include "../utils/helpFuncs.h"
#include "iostream"
#include "conio.h"

#define HUMAN_POWER 5
#define HUMAN_POWER_DURATION 5
#define HUMAN_POWER_COOLDOWN 5
#define HUMAN_STRENGTH 5
#define HUMAN_INITIATIVE 4
#define HUMAN_SYMBOL 'H'

#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80

using namespace std;

Human::Human(int x, int y, World *world) : Animal(x, y, world, HUMAN_STRENGTH, HUMAN_INITIATIVE, HUMAN_SYMBOL) {
    this->powerCounter = 0;
    this->powerCooldownCounter = 0;
    this->isPowerActive = false;
    this->isPowerOnCooldown = false;
    this->type = "Human";
}

void Human::action() {
    int newX = this->x;
    int newY = this->y;
    char direction;
    cout << "Choose direction (WASD), use power (P), save game (S) or load (L): ";
    while (true)
    {
        direction = (char)_getch();
        if (direction == 'p') this->usePower();
        else if (direction == 's') this->world->saveToFile("savegame.txt", this);
        else if (direction == 'l') {
            Human* loadedHuman = (Human*)this->world->loadFromFile("savegame.txt");
            this->x = loadedHuman->x;
            this->y = loadedHuman->y;
            this->powerCounter = loadedHuman->powerCounter;
            this->powerCooldownCounter = loadedHuman->powerCooldownCounter;
            this->isPowerActive = loadedHuman->isPowerActive;
            this->isPowerOnCooldown = loadedHuman->isPowerOnCooldown;
            this->endGame = loadedHuman->endGame;
            this->world->moveOrganism(this, this->x, this->y);
            delete loadedHuman;
            return;
        }
        else if (direction == 'q') {
            this->EndGame();
            return;
        }
        else if (direction == UP_ARROW || direction == LEFT_ARROW || direction == RIGHT_ARROW || direction == DOWN_ARROW) { break; }
    }
    switch (direction) {
        case UP_ARROW:
            newY--;
            break;
        case LEFT_ARROW:
            newX--;
            break;
        case DOWN_ARROW:
            newY++;
            break;
        case RIGHT_ARROW:
            newX++;
            break;
        default:
            break;
    }
    if (!isOnMap(newX, newY, this->world->getWidth(), this->world->getHeight())) { return; }
    this->world->makeMove(this, newX, newY);
    this->powerTick();
}

void Human::powerCooldownTick() {
    this->powerCooldownCounter++;
    this->world->MakeComment("Human special power cooldown: " + to_string(HUMAN_POWER_COOLDOWN - this->powerCooldownCounter));
    if (this->powerCooldownCounter >= HUMAN_POWER_COOLDOWN)
    {
        this->powerCooldownCounter = 0;
        this->isPowerOnCooldown = false;
    }
}

void Human::powerDurationTick() {
    this->powerCounter++;
    this->world->MakeComment("Human special power duration: " + to_string(HUMAN_POWER_DURATION - this->powerCounter));
    this->setStrength(this->getStrength() - 1);
    if (this->powerCounter >= HUMAN_POWER_DURATION)
    {
        this->powerCounter = 0;
        this->isPowerActive = false;
        this->isPowerOnCooldown = true;
    }
}

void Human::powerTick() {
    if (this->isPowerActive) { this->powerDurationTick(); }
    else if (this->isPowerOnCooldown) { this->powerCooldownTick(); }
}

void Human::usePower() {
    if (!this->isPowerActive && !this->isPowerOnCooldown)
    {
        // chosen power is magical potion that increases strength by 5 and each turn decreases it by 1
        this->isPowerActive = true;
        this->setStrength(this->getStrength() + HUMAN_POWER);
        this->world->MakeComment("Human used magical potion. Strength increased by 5.");
    }
}

bool Human::isEndGame() const {
    return this->endGame;
}

void Human::EndGame() {
    this->endGame = true;
}

void Human::death() {
    this->alive = false;
    this->EndGame();
}

std::string Human::getSpecieName() const {
    return "Human";
}

void Human::saveToFile(std::ostream &file) {
    file << this->getSpecieName() << " " << this->x << " " << this->y << " " << this->getStrength() << " " << this->getInitiative() << " " << this->getAge() << " " << this->isPowerActive << " " << this->isPowerOnCooldown << " " << this->powerCounter << " " << this->powerCooldownCounter << " " << this->endGame << endl;
}

void Human::setPowerActive(bool nIsPowerActive) {
    this->isPowerActive = nIsPowerActive;
}

void Human::setPowerOnCooldown(bool nIsPowerOnCooldown) {
    this->isPowerOnCooldown = nIsPowerOnCooldown;
}

void Human::setPowerCounter(int nPowerCounter) {
    this->powerCounter = nPowerCounter;
}

void Human::setPowerCooldownCounter(int nPowerCooldownCounter) {
    this->powerCooldownCounter = nPowerCooldownCounter;
}

void Human::setEndGame(bool nEndGame) {
    this->endGame = nEndGame;
}