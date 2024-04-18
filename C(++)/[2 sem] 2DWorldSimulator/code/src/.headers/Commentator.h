//
// Created by szymo on 4/24/2023.
//

#ifndef DEV_COMMENTATOR_H
#define DEV_COMMENTATOR_H

#include "string"
#include "../worldObjects/.headers/Organism.h"
#include "vector"

using namespace std;

class Commentator {
public:
    Commentator() = default;
    ~Commentator() = default;
    void commentFight(Organism *attacker, Organism *defender, bool won);
    void commentEat(Organism *eater, Organism *eaten);
    void commentMultiply(Organism *parent1, Organism *parent2, Organism *child);
    void comment(const string& comment);
    void newRound();
    void introduceAuthor();
    void printComments();
    int getCurrentRound() const;
    void setCurrentRound(int newCurrentRound);
private:
    std::vector<string> comments;
    string author = "Szymon Kasprzycki 193065";
    int currentRoundComments = 0;
    int currentRound = 0;
};


#endif //DEV_COMMENTATOR_H
