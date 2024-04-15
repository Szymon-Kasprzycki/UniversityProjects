#include "SelectorList.h"
#include "CustomString.h"

SelectorList::SelectorList() {
    this->head = nullptr;
    size = 0;
}

SelectorList::~SelectorList() {
    this->clear();
}

void SelectorList::pushFront(CustomString *value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = this->head;
    this->head = newNode;
    this->size++;
}

void SelectorList::pushBack(CustomString *value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    if (this->head == nullptr) this->head = newNode;
    else {
        Node *current = this->head;
        while (current->next != nullptr) current = current->next;
        current->next = newNode;
    }
    this->size++;
}

void SelectorList::popFront() {
    if (this->head == nullptr) return;
    Node *node = this->head;
    this->head = this->head->next;
    delete[] node;
    this->size--;
}

void SelectorList::popBack() {
    if (this->head == nullptr) return;
    Node *current = this->head;
    while (current->next->next != nullptr) current = current->next;
    Node *node = current->next;
    current->next = nullptr;
    this->size--;
    delete[] node;
}

void SelectorList::insert(int index, CustomString *value) {
    if (index < 0 || index > this->size) return;
    if (index == 0) {
        this->pushFront(value);
        return;
    }
    if (index == this->size) {
        this->pushBack(value);
        return;
    }
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    Node *current = this->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    this->size++;
}

void SelectorList::remove(int index) {
    if (index < 0 || index >= this->size) return;
    if (index == 0) {
        this->popFront();
        return;
    }
    if (index == this->size - 1) {
        this->popBack();
        return;
    }
    Node *current = this->head;
    for (int i = 0; i < index - 1; i++) current = current->next;
    Node *node = current->next;
    current->next = current->next->next;
    this->size--;
    delete node;
}

// Get index of value in list, return -1 if not found
int SelectorList::getIndexOf(const CustomString *value) const {
    int index = 0;
    Node *current = this->head;
    while (current != nullptr) {
        if (*(current->value) == *value) return index;
        index++;
        current = current->next;
    }
    return -1;
}

void SelectorList::clear() {
    if (this->isEmpty()) return;
    while (this->head != nullptr) {
        Node *node = this->head;
        this->head = this->head->next;
        delete node;
    }
    this->size = 0;
}

void SelectorList::copy(const SelectorList &other) {
    Node *current = other.head;
    while (current != nullptr) {
        this->pushBack(current->value);
        current = current->next;
    }
}

int SelectorList::getSize() const {
    return this->size;
}

bool SelectorList::isEmpty() const {
    return size == 0;
}

CustomString *SelectorList::get(int index) {
    if (index < 0 || index >= this->size || this->size == 0) {
        return nullptr;
    }
    Node *current = this->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}