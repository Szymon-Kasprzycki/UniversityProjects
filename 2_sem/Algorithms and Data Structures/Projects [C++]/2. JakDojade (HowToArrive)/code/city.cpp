#include "City.h"

City::City(int x, int y, int index, MyString *name, bool has_any_route) {
    this->x = x;
    this->y = y;
    this->index = index;
    this->name = name;
    this->has_any_route = has_any_route;
}

City::City() {
    this->x = -1;
    this->y = -1;
    this->index = -1;
    this->name = nullptr;
    this->has_any_route = false;
}

City::~City() {
    delete this->name;
}