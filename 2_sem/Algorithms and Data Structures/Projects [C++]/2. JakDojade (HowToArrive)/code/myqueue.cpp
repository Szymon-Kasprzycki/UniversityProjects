#include "MyQueue.h"
#include <iostream>

MyQueue::MyQueue() {
    front = nullptr;
    rear = nullptr;
}

MyQueue::~MyQueue() {
    this->clear();
}

void MyQueue::enqueue(int data) {
    Node *newNode = new Node;
    newNode->val = data;
    newNode->next = nullptr;
    if (rear == nullptr) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

int MyQueue::dequeue() {
    if (front == nullptr) return -1;

    Node *temp = front;
    int result = temp->val;
    front = front->next;
    if (front == nullptr) rear = nullptr;

    delete temp;
    return result;
}

bool MyQueue::isEmpty() const {
    return front == nullptr;
}

void MyQueue::clear() {
    Node *curr = front;
    while (curr != nullptr) {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
    front = nullptr;
    rear = nullptr;
}