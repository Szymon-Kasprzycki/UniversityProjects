//
// Created by szymo on 4/24/2023.
//

#include ".headers/Commentator.h"
#include "iostream"

#define MAX_COMMENTS_PER_ROUND 8

void Commentator::comment(const string& comment) {
    comments.push_back(comment);
    currentRoundComments++;
}

void Commentator::newRound() {
    comments.clear();
    currentRoundComments = 0;
    currentRound++;
    comments.push_back("Round " + to_string(currentRound));
}

void Commentator::introduceAuthor() {
    cout << "Author: " << author << endl;
}

void Commentator::commentFight(Organism *attacker, Organism *defender, bool won) {
    string comment = attacker->getSpecieName() + " attacked " + defender->getSpecieName() + " and ";
    if (won) {
        comment += "won";
    } else {
        comment += "lost";
    }
    this->comment(comment);
}

void Commentator::printComments() {
    int counter = 0;
    for (auto &comment : comments) {
        cout << comment << endl;
        counter++;
        if (counter > MAX_COMMENTS_PER_ROUND) return;
    }
}

void Commentator::commentEat(Organism *eater, Organism *eaten) {
    string comment = eater->getSpecieName() + " ate " + eaten->getSpecieName();
    this->comment(comment);
}

int Commentator::getCurrentRound() const {
    return currentRound;
}

void Commentator::setCurrentRound(int newCurrentRound) {
    this->currentRound = newCurrentRound;
    comments.clear();
    comments.push_back("Round " + to_string(currentRound));
}