//
// Created by szymo on 4/10/2023.
//

#include "iostream"
#include ".headers/World.h"
#include "worldObjects/.headers/Organism.h"
#include "worldObjects/.headers/Animal.h"
#include "worldObjects/.headers/Human.h"
#include "utils/helpFuncs.h"
#include "worldObjects/animals/.headers/Antelope.h"
#include "worldObjects/animals/.headers/Wolf.h"
#include "worldObjects/animals/.headers/Turtle.h"
#include "worldObjects/plants/.headers/Belladonna.h"
#include "worldObjects/plants/.headers/SosnowskyHogweed.h"
#include "worldObjects/plants/.headers/Guarana.h"
#include "worldObjects/plants/.headers/Grass.h"
#include "worldObjects/animals/.headers/Sheep.h"
#include "worldObjects/animals/.headers/Fox.h"
#include "worldObjects/plants/.headers/SowThistle.h"
#include <fstream>

using namespace std;

World::World(int w, int h) {
    this->width = w;
    this->height = h;
    this->map = nullptr;
    this->queue = std::vector<Organism *>();
    this->toDelete = std::vector<Organism *>();
    this->allOrganisms = std::list<Organism *>();
    this->commentator = new Commentator();
    this->initWorld();
}

World::~World() {
    this->destroyWorld();
}

void World::initWorld() {
    this->map = new Organism **[this->width];
    for (int i = 0; i < this->height; i++) {
        this->map[i] = new Organism *[this->width];
        for (int j = 0; j < this->width; j++) this->map[i][j] = nullptr;
    }

}

void World::destroyWorld() {
    for (int i = 0; i < this->height; i++) { delete[] this->map[i]; }
    delete[] this->map;

    for (auto &allOrganism : this->allOrganisms) {
        if (allOrganism->getType() == "Human") { continue; }
        delete allOrganism;
    }
    this->allOrganisms.clear();
    this->queue.clear();
    this->toDelete.clear();
}

void World::drawWorld() {
    commentator->introduceAuthor();
    for (int i = 0; i < (this->height+2); i++)
    {
        for (int j = 0; j < (this->width+2); j++)
        {
            if (i == 0 || i == (this->height+1) || j == 0 || j == (this->width+1)) { cout << "*"; }
            else if (this->map[i-1][j-1] != nullptr) this->map[i-1][j-1]->draw();
            else cout << " ";
        }
        cout << endl;
    }
    commentator->printComments();
    commentator->newRound();
}

void World::addOrganism(Organism *organism) {
    if (!isOnMap(organism->getX(), organism->getY(), this->width, this->height)) return;
    this->map[organism->getY()][organism->getX()] = organism;
    this->allOrganisms.push_back(organism);
}

// Make a loop of removing organisms instead of removing in time
// because of removing while iterating
void World::removeOrganism(Organism *organism) {
    this->map[organism->getY()][organism->getX()] = nullptr;
    organism->death();
    toDelete.push_back(organism);
}

void World::removeOrganism(int x, int y) {
    if (!isOnMap(x, y, this->width, this->height)) return;
    Organism *organism = this->map[y][x];
    if (organism != nullptr) {
        this->map[y][x] = nullptr;
        organism->death();
        toDelete.push_back(organism);
    }
}

void World::moveOrganism(Organism *organism, int x, int y) {
    this->map[organism->getY()][organism->getX()] = nullptr;
    organism->setX(x);
    organism->setY(y);
    this->map[y][x] = organism;
}

void World::makeMove(Organism *organism, int x, int y) {
    Organism* opponent = this->getOrganism(x, y);
    if (opponent != nullptr)
    {
        Organism* temp = opponent->collision(organism);
        if (temp == organism)
        {
            this->removeOrganism(opponent);
            this->moveOrganism(organism, x, y);
            if (opponent->getType() == "Plant") { commentator->commentEat(organism, opponent); }
            else { commentator->commentFight(organism, opponent, true); }
        }
        else if (temp == opponent)
        {
            this->removeOrganism(organism);
            commentator->commentFight(organism, opponent, false);
        }
        else {
            if (organism->getType() == "Animal" && ((Animal *)organism)->isAntelope())
            {
                // In this case, antelope escaped from opponent
                this->moveOrganism(organism, x, y);
                commentator->comment("Antelope escaped from fight!");
            }
            else if (opponent->getSpecieName() == "Turtle")
            {
                // In this case, turtle blocked opponent
                commentator->comment("Turtle blocked opponent!");
            }
            return;
        }
    }
    else {
        this->moveOrganism(organism, x, y);
    }
}

Organism *World::getOrganism(int x, int y) {
    return this->map[y][x];
}

void World::makeTurn() {
    // Make turn for every organism, organism with higher initiative will move first
    // If two organisms have the same initiative, the one that was added to the world first will move first
    this->queue.clear();

    // TODO, sorting using sort() function with bool

    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            Organism *temp = this->getOrganism(j, i);
            if (temp != nullptr && temp->getType() != "Human")
            {
                this->queue.push_back(temp);
            }
        }
    }

    // Sort queue
    for (int i = 0; i < this->queue.size(); i++)
    {
        for (int j = 0; j < this->queue.size() - 1; j++)
        {
            if (this->queue[j]->getInitiative() < this->queue[j + 1]->getInitiative())
            {
                Organism *temp = this->queue[j];
                this->queue[j] = this->queue[j + 1];
                this->queue[j + 1] = temp;
            }
            // If two organisms have the same initiative, the one that was added to the world first will move first
            else if (this->queue[j]->getInitiative() == this->queue[j + 1]->getInitiative())
            {
                if (this->queue[j]->getAge() < this->queue[j + 1]->getAge())
                {
                    Organism *temp = this->queue[j];
                    this->queue[j] = this->queue[j + 1];
                    this->queue[j + 1] = temp;
                }
            }
        }
    }

    // main loop of action invoke
    for (auto & i : this->queue)
    {
        if (i != nullptr && i->isAlive())
        {
            i->action();
            // Update age of organism
            i->setAge(i->getAge() + 1);
        }
    }

    this->queue.clear();
    for (auto & i : this->toDelete) {
        this->allOrganisms.remove(i);
        delete i;
    }
    this->toDelete.clear();
}

int World::getWidth() const { return this->width; }

int World::getHeight() const { return this->height; }


void World::findFreeNeighbourCell(int x, int y, int &newX, int &newY) {
    int xPossible[4];
    int yPossible[4];
    int possibleMoves = 0;
    if (isOnMap(x-1, y, this->width, this->height) && this->getOrganism(x-1, y) == nullptr)
    {
        xPossible[possibleMoves] = x-1;
        yPossible[possibleMoves] = y;
        possibleMoves++;
    }
    if (isOnMap(x+1, y, this->width, this->height) && this->getOrganism(x+1, y) == nullptr)
    {
        xPossible[possibleMoves] = x+1;
        yPossible[possibleMoves] = y;
        possibleMoves++;
    }
    if (isOnMap(x, y-1, this->width, this->height) && this->getOrganism(x, y-1) == nullptr)
    {
        xPossible[possibleMoves] = x;
        yPossible[possibleMoves] = y-1;
        possibleMoves++;
    }
    if (isOnMap(x, y+1, this->width, this->height) && this->getOrganism(x, y+1) == nullptr)
    {
        xPossible[possibleMoves] = x;
        yPossible[possibleMoves] = y+1;
        possibleMoves++;
    }
    if (possibleMoves > 0) {
        int position = random(0, possibleMoves-1);
        newX = xPossible[position];
        newY = yPossible[position];
    } else {
        newX = -1;
        newY = -1;
    }
}

void World::MakeComment(const std::string &comment) {
    this->commentator->comment(comment);
}

void World::saveToFile(const std::string &fileName, Organism* human) {
    std::ofstream file;
    file.open(fileName);
    if (file.is_open())
    {
        file << this->width << " " << this->height << std::endl;
        // write commentator round
        file << this->commentator->getCurrentRound() << std::endl;
        // write organisms amount
        file << this->allOrganisms.size() << std::endl;
        for (auto & i : this->allOrganisms)
        {
            if (i->getSpecieName() == "Human") continue;
            else file << i->getSpecieName() << " " << i->getX() << " " << i->getY() << " " << i->getStrength() << " " << i->getInitiative() << " " << i->getAge() << std::endl;
        }
        ((Human*)human)->saveToFile(file);
        file.close();
    }
}

Organism* World::loadFromFile(const std::string &fileName) {
    std::ifstream file;
    file.open(fileName);
    Organism *human = nullptr;
    if (file.is_open())
    {
        this->destroyWorld();
        // read width and height
        file >> width >> height;
        this->initWorld();
        // read commentator round
        int commentatorRound;
        file >> commentatorRound;
        this->commentator->setCurrentRound(commentatorRound);
        // read organisms
        int organismsAmount;
        file >> organismsAmount;
        for (int i = 0; i < organismsAmount; i++)
        {
            std::string specieName;
            int x, y, strength, initiative, age;
            file >> specieName >> x >> y >> strength >> initiative >> age;
            // Save human as special, because he is controlling main loop
            if (specieName == "Human")
            {
                int isPowerActive, isPowerOnCooldown, powerCounter, powerCooldownCounter, endGame;
                file >> isPowerActive >> isPowerOnCooldown >> powerCounter >> powerCooldownCounter >> endGame;
                human = this->createOrganism(specieName, x, y);
                ((Human *)human)->setPowerActive(isPowerActive);
                ((Human *)human)->setPowerOnCooldown(isPowerOnCooldown);
                ((Human *)human)->setPowerCounter(powerCounter);
                ((Human *)human)->setPowerCooldownCounter(powerCooldownCounter);
                ((Human *)human)->setEndGame(endGame);
                continue;
            }
            Organism *temp = this->createOrganism(specieName, x, y);
            if (temp == nullptr) continue;
            temp->setAge(age);
            temp->setStrength(strength);
            temp->setInitiative(initiative);
            this->addOrganism(temp);
        }
    }
    file.close();
    return human;
}

Organism* World::createOrganism(const std::string &specieName, int x, int y) {
    if (specieName == "Antelope") return new Antelope(x,y,this);
    else if (specieName == "Fox") return new Fox(x,y,this);
    else if (specieName == "Sheep") return new Sheep(x,y,this);
    else if (specieName == "Turtle") return new Turtle(x,y,this);
    else if (specieName == "Wolf") return new Wolf(x,y,this);
    else if (specieName == "Human") return new Human(x,y,this);
    else if (specieName == "Grass") return new Grass(x,y,this);
    else if (specieName == "Guarana") return new Guarana(x,y,this);
    else if (specieName == "Belladonna") return new Belladonna(x,y,this);
    else if (specieName == "SosnowskyHogweed") return new SosnowskyHogweed(x,y,this);
    else if (specieName == "SowThistle") return new SowThistle(x,y,this);
    else return nullptr;
}