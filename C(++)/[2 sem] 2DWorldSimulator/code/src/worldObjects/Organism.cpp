//
// Created by szymo on 4/10/2023.
//

#include ".headers/Organism.h"
#include "iostream"

using namespace std;

Organism::Organism(int x, int y, int strength, int initiative, char symbol, int age)
{
    this->x = x;
    this->y = y;
    this->strength = strength;
    this->initiative = initiative;
    this->age = age;
    this->symbol = symbol;
    this->type = "Organism";
    this->alive = true;
}

void Organism::death() { this->alive = false; }

bool Organism::isAlive() const { return this->alive; }

int Organism::getX() const { return this->x; }

int Organism::getY() const { return this->y; }

int Organism::getStrength() const { return this->strength; }

int Organism::getInitiative() const { return this->initiative; }

int Organism::getAge() const { return this->age; }

char Organism::getSymbol() const { return this->symbol; }

std::string Organism::getType() { return this->type; }

void Organism::setX(int newX) { this->x = newX; }

void Organism::setY(int newY) { this->y = newY; }

void Organism::setStrength(int newStrength) { this->strength = newStrength; }

void Organism::setInitiative(int newInitiative) { this->initiative = newInitiative; }

void Organism::setAge(int newAge) { this->age = newAge; }

void Organism::setSymbol(char newSymbol) { this->symbol = newSymbol; }

void Organism::draw() { cout << this->symbol; }

string Organism::getSpecieName() const { return "Organism"; }

Organism::~Organism() = default;
