#ifndef BASIC_ATTRIBUTELIST_H
#define BASIC_ATTRIBUTELIST_H

#include "SelectorList.h"

class AttributeList {
private:
    int size;
    struct Node {
        CustomString *name;
        CustomString *value;
        Node *next;
    };
    Node *head;
public:
    AttributeList();

    ~AttributeList();

    void insert(CustomString *attribute, CustomString *value);

    bool remove(CustomString *attribute);

    CustomString *get(CustomString *name);

    void setValue(CustomString *attribute, CustomString *value);

    void copy(const AttributeList &other);

    int getSize() const;

    bool isEmpty() const;

    void clear();
};


#endif //BASIC_ATTRIBUTELIST_H