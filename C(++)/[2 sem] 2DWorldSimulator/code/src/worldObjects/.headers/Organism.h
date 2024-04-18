//
// Created by szymo on 4/10/2023.
//

#ifndef DEV_ORGANISM_H
#define DEV_ORGANISM_H

#include "string"


class Organism {
private:
public:
    Organism(int x, int y, int strength, int initiative, char symbol, int age);
    virtual ~Organism();
    int getX() const;
    int getY() const;
    int getStrength() const;
    int getInitiative() const;
    int getAge() const;
    char getSymbol() const;
    std::string getType();
    void setX(int newX);
    void setY(int newY);
    void setStrength(int newStrength);
    void setInitiative(int newInitiative);
    void setAge(int newAge);
    void setSymbol(char newSymbol);
    virtual void action() = 0; // pure virtual function
    virtual Organism *collision(Organism *pOrganism) = 0; // pure virtual function
    virtual void draw(); // maybe! pure virtual function
    bool isAlive() const;
    virtual void death();
    virtual std::string getSpecieName() const;
protected:
    // Position
    int x;
    int y;
    // Properties
    int strength;
    int initiative;
    // Age on the map (turns alive)
    int age;
    // Symbol on the map
    char symbol;
    // Type of the organism (Animal, Plant, Human, etc.)
    std::string type;
    bool alive;
};


#endif //DEV_ORGANISM_H
