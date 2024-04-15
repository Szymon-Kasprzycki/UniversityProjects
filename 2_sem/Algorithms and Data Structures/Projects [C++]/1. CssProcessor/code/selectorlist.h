#ifndef BASIC_SELECTORLIST_H
#define BASIC_SELECTORLIST_H

#include "CustomString.h"

class SelectorList {
private:
    struct Node {
        CustomString *value;
        Node *next;
    };
    Node *head;
    int size;
public:
    SelectorList();

    ~SelectorList();

    void pushFront(CustomString *value);

    void pushBack(CustomString *value);

    void popFront();

    void popBack();

    void insert(int index, CustomString *value);

    void remove(int index);

    CustomString *get(int index);

    void clear();

    void copy(const SelectorList &other);

    int getSize() const;

    bool isEmpty() const;

    int getIndexOf(const CustomString *value) const;

};


#endif //BASIC_SELECTORLIST_H
