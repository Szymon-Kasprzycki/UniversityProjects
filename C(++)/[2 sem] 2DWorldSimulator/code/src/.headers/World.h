//
// Created by szymo on 4/10/2023.
//

#ifndef DEV_WORLD_H
#define DEV_WORLD_H

#include "../worldObjects/.headers/Organism.h"
#include "../.headers/Commentator.h"
#include <vector>
#include <list>

class World {
private:
    int width;
    int height;
    Organism ***map;
    Commentator *commentator;
    std::list<Organism *> allOrganisms;
    std::vector<Organism *> queue;
    std::vector<Organism *> toDelete;
public:
    World(int w, int h);
    ~World();
    void makeTurn();
    void drawWorld();
    void addOrganism(Organism *organism);
    void moveOrganism(Organism *organism, int x, int y);
    int getWidth() const;
    int getHeight() const;
    Organism *getOrganism(int x, int y);
    void findFreeNeighbourCell(int x, int y, int &newX, int &newY);
    void removeOrganism(int x, int y);
    void makeMove(Organism *organism, int x, int y);
    void MakeComment(const string& comment);
    void saveToFile(const string& fileName, Organism* human);
    Organism* loadFromFile(const string& fileName);
protected:
    Organism* createOrganism(const string& specieName, int x, int y);
    void removeOrganism(Organism *organism);
    void initWorld();
    void destroyWorld();
};


#endif //DEV_WORLD_H
