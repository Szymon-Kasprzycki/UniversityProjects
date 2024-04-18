#include "AttributeList.h"

AttributeList::AttributeList() {
    this->head = nullptr;
    this->size = 0;
}

AttributeList::~AttributeList() {
    this->clear();
}

void AttributeList::insert(CustomString *attribute, CustomString *value) {
    Node *newNode = new Node();
    newNode->name = attribute;
    newNode->value = value;
    newNode->next = nullptr;
    if (this->isEmpty()) this->head = newNode;
    else {
        Node *current = this->head;
        while (current->next != nullptr) current = current->next;
        current->next = newNode;
    }
    this->size++;
}

bool AttributeList::remove(CustomString *attribute) {
    if (this->isEmpty()) return false;
    Node *current = this->head;
    Node *previous = nullptr;
    while (current != nullptr) {
        if (*(current->name) == *attribute) {
            if (previous == nullptr) this->head = current->next;
            else previous->next = current->next;
            delete current;
            this->size--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

CustomString *AttributeList::get(CustomString *name) {
    if (this->isEmpty()) return nullptr;
    CustomString *value = nullptr;
    Node *current = this->head;
    while (current != nullptr) {
        if (*(current->name) == *name) return current->value;
        current = current->next;
    }
    return value;
}

void AttributeList::setValue(CustomString *attribute, CustomString *value) {
    if (this->isEmpty()) return;
    Node *current = this->head;
    while (current != nullptr) {
        if (*(current->name) == *attribute) {
            current->value = value;
            return;
        }
        current = current->next;
    }
}

void AttributeList::copy(const AttributeList &other) {
    if (other.head == nullptr) return;
    Node *current = other.head;
    while (current != nullptr) {
        this->insert(current->name, current->value);
        current = current->next;
    }
}

int AttributeList::getSize() const {
    return this->size;
}

bool AttributeList::isEmpty() const {
    return this->size == 0;
}

void AttributeList::clear() {
    if (this->isEmpty()) return;
    Node *current = this->head;
    Node *next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    this->head = nullptr;
    this->size = 0;
}