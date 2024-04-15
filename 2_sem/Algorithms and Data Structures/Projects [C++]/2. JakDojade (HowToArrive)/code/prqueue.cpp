#include "PrQueue.h"


PrQueue::PrQueue() {
    head = nullptr;
}

PrQueue::~PrQueue() {
    while (head != nullptr) {
        PrQNode *temp = head;
        head = head->next;
        delete temp;
    }
}

void PrQueue::insert(int value, int priority) {
    auto *newNode = new PrQNode;
    newNode->value = value;
    newNode->priority = priority;
    newNode->next = nullptr;

    if (head == nullptr || priority <= head->priority) {
        newNode->next = head;
        head = newNode;
    } else {
        PrQNode *current = head;
        while (current->next != nullptr && priority > current->next->priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int PrQueue::pop() {
    if (head == nullptr) { return -1; }
    PrQNode *temp = head;
    head = head->next;
    int value = temp->value;
    delete temp;
    return value;
}

bool PrQueue::isEmpty() const {
    return head == nullptr;
}