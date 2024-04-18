//
// Created by szymo on 4/16/2023.
//

#include "helpFuncs.h"
#include "random"

int random(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

bool isOnMap(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
}