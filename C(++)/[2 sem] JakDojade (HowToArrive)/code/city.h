#ifndef TEST_CITY_H
#define TEST_CITY_H

#include "MyString.h"

class City {
public:
    int x;
    int y;
    int index;
    MyString *name;
    bool has_any_route;

    City(int x, int y, int index, MyString *name, bool has_any_route);

    City();

    ~City();
};


#endif //TEST_CITY_H
