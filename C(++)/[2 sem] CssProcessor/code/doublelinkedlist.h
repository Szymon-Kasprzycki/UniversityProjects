#ifndef BASIC_DOUBLELINKEDLIST_H
#define BASIC_DOUBLELINKEDLIST_H

#include "iostream"
#include "CssSection.h"

class DoubleLinkedList {
private:
    int size;
    int T;
    struct Block {
        int occupied = 0;
        CssSection **values = nullptr;
        Block *next = nullptr;
        Block *prev = nullptr;
    };
    Block *head;
    Block *tail;
public:
    explicit DoubleLinkedList(int newT);

    DoubleLinkedList(const DoubleLinkedList &other);

    ~DoubleLinkedList();

    int getSize() const;

    int getT() const;

    void clear();

    void copy(const DoubleLinkedList &other);

    DoubleLinkedList &operator=(const DoubleLinkedList &other);

    Block *allocateNewNode();

    void deallocateNode(Block *node);

    void removeNode(Block *node);

    void insertNode(Block *node);

    void addCssSection(CssSection *cssSection);

    bool removeCssSection(int index);

    CssSection *getCssSection(int index);

    int getPropertiesCount(CustomString &name);

    int getSelectorsCount(CustomString &name);

    CustomString *getSelectorAttributeValue(CustomString &selector, CustomString &attribute);

    bool removeAttributeFromSectionIndex(int index, CustomString *attribute);

};


#endif //BASIC_DOUBLELINKEDLIST_H
