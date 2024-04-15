#ifndef TEST_HASHMAP_H
#define TEST_HASHMAP_H

#include "City.h"
#include "MyString.h"

class HashMap {
private:
    struct Node {
        City *value;
        Node *next;

        explicit Node(City *val);

        Node();
    };

    Node **table;

public:
    HashMap();

    HashMap(const HashMap &src);

    HashMap &operator=(const HashMap &src);

    ~HashMap();

    static unsigned long hashCityName(MyString &name);

    static unsigned long hashCityName(const char *name);

    City *get(MyString &name);

    void add(City *src);

    void remove(MyString &name);
};


#endif //TEST_HASHMAP_H
