#include "DoubleLinkedList.h"
#include "CssSection.h"

using namespace std;

DoubleLinkedList::DoubleLinkedList(const int newT) {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    this->T = newT;
}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList &other) {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    this->T = 0;
    this->copy(other);
}

DoubleLinkedList &DoubleLinkedList::operator=(const DoubleLinkedList &other) {
    if (this != &other) {
        this->copy(other);
    }
    return *this;
}

DoubleLinkedList::~DoubleLinkedList() {
    this->clear();
}

DoubleLinkedList::Block *DoubleLinkedList::allocateNewNode() {
    auto *newNode = new Block;
    newNode->values = new CssSection *[this->T];
    for (int i = 0; i < this->T; i++) newNode->values[i] = nullptr;
    newNode->occupied = 0;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    this->insertNode(newNode);
    return newNode;
}

void DoubleLinkedList::removeNode(DoubleLinkedList::Block *node) {
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    if (this->head == node) {
        this->head = node->next;
    }
    if (this->tail == node) {
        this->tail = node->prev;
    }
    this->deallocateNode(node);
}

void DoubleLinkedList::deallocateNode(DoubleLinkedList::Block *node) {
    for (int i = 0; i < this->getT(); i++) {
        // Delete the value if it is not null
        if (node->values[i] != nullptr) delete node->values[i];
    }
    delete[] node->values;
    delete node;
}

// Insert node at the end of the list
void DoubleLinkedList::insertNode(DoubleLinkedList::Block *node) {
    if (this->head == nullptr) {
        this->head = node;
    }
    if (this->tail != nullptr) {
        this->tail->next = node;
    }
    node->prev = this->tail;
    this->tail = node;
}

void DoubleLinkedList::addCssSection(CssSection *cssSection) {
    if (this->head == nullptr) this->allocateNewNode();
    Block *temp = this->tail;
    // If the last node is full, allocate a new node
    if (temp->occupied == this->getT()) temp = this->allocateNewNode();
    // Add the new value to the node
    for (int i = 0; i < this->getT(); i++) {
        if (temp->values[i] == nullptr) {
            temp->values[i] = cssSection;
            temp->occupied++;
            this->size++;
            return;
        }
    }
}

bool DoubleLinkedList::removeCssSection(int index) {
    int status = 0;
    if (this->size == 0) return false;

    Block *temp = this->head;
    int i = 0;
    // Find the node that contains the value at the given index
    while (i + temp->occupied < index) {
        if (temp->next == nullptr) break;
        i += temp->occupied;
        temp = temp->next;
    }
    // Remove the value from the node
    int counter = 0;
    index = index - i;
    for (int j = 0; j < this->getT(); j++) {
        if (temp->values[j] != nullptr) {
            counter++;
            if (counter == index) {
                delete temp->values[j];
                temp->values[j] = nullptr;
                temp->occupied--;
                this->size--;
                status = 1;
            }
        }
    }
    // If the node is empty, remove it
    if (temp->occupied == 0) {
        this->removeNode(temp);
    } else if (status == 1) {
        for (int j = 0; j < this->getT(); j++) {
            // if the value is nullptr, move it to the end of the node
            if (temp->values[j] == nullptr) {
                for (int k = j + 1; k < this->getT(); k++) {
                    if (temp->values[k] != nullptr) {
                        temp->values[j] = temp->values[k];
                        temp->values[k] = nullptr;
                        break;
                    }
                }
            }
        }
    }
    return status;
}

CssSection *DoubleLinkedList::getCssSection(int index) {
    if (this->size == 0 || index < 0 || index > this->size) return nullptr;
    Block *temp = this->head;
    int i = 0;
    while (i + temp->occupied < index) {
        if (temp->next == nullptr) break;
        i += temp->occupied;
        temp = temp->next;
    }
    int counter = 0;
    index = index - i;
    for (int j = 0; j < this->getT(); j++) {
        if (temp->values[j] != nullptr) {
            counter++;
            if (counter == index) return temp->values[j];
        }
    }
    return nullptr;
}

void DoubleLinkedList::clear() {
    Block *temp = this->head;
    while (temp != nullptr) {
        Block *next = temp->next;
        this->deallocateNode(temp);
        temp = next;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

int DoubleLinkedList::getSize() const {
    return this->size;
}

int DoubleLinkedList::getT() const {
    return this->T;
}

void DoubleLinkedList::copy(const DoubleLinkedList &other) {
    this->clear();
    this->T = other.getT();
    Block *temp = other.head;
    while (temp != nullptr) {
        Block *newNode = this->allocateNewNode();
        for (int i = 0; i < this->getT(); i++) {
            if (temp->values[i] != nullptr) {
                newNode->values[i] = new CssSection(*temp->values[i]);
                newNode->occupied++;
            }
        }
        temp = temp->next;
    }
    this->size = other.size;
}

int DoubleLinkedList::getPropertiesCount(CustomString &name) {
    int count = 0;
    Block *temp = this->head;
    while (temp != nullptr) {
        for (int i = 0; i < this->getT(); i++) // for each section in the block
        {
            if (temp->values[i] != nullptr) {
                if (temp->values[i]->getAttribute(&name) != nullptr) count++;
            }
        }
        temp = temp->next;
    }
    return count;
}

int DoubleLinkedList::getSelectorsCount(CustomString &name) {
    int count = 0;
    Block *temp = this->head;
    while (temp != nullptr) {
        for (int i = 0; i < this->getT(); i++) // for each section in the block
        {
            if (temp->values[i] != nullptr) {
                // Doubled selectors (in one section) are not counted
                if (temp->values[i]->getSelector(&name) != nullptr) count++;
            }
        }
        temp = temp->next;
    }
    return count;
}

CustomString *DoubleLinkedList::getSelectorAttributeValue(CustomString &selector, CustomString &attribute) {
    Block *temp = this->tail;
    CustomString *attributeValue;
    CustomString *selectorValue;
    while (temp != nullptr) {
        for (int i = this->getT() - 1; i >= 0; i--) // for each section in the block
        {
            if (temp->values[i] != nullptr) {
                selectorValue = temp->values[i]->getSelector(&selector);
                if (selectorValue != nullptr) {
                    attributeValue = temp->values[i]->getAttribute(&attribute);
                    if (attributeValue != nullptr) return attributeValue;
                }
            }
        }
        temp = temp->prev;
    }
    return nullptr;
}

bool DoubleLinkedList::removeAttributeFromSectionIndex(int index, CustomString *attribute) {
    CssSection *target = this->getCssSection(index);
    if (target == nullptr) return false;
    int status = target->removeAttribute(attribute);
    if (target->isEmpty()) this->removeCssSection(index);

    return status;
}