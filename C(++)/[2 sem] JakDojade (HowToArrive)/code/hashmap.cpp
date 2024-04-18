#include "HashMap.h"
#include "iostream"

#define CHARS_POSSIBLE 75

using namespace std;

const int TABLE_SIZE = CHARS_POSSIBLE * CHARS_POSSIBLE * CHARS_POSSIBLE;
const int hashWeights[3] = {1061, 347, 127}; // Prime numbers for hashing


HashMap::Node::Node(City *val) {
    value = val;
    next = nullptr;
}

HashMap::Node::Node() {
    value = nullptr;
    next = nullptr;
}

HashMap::HashMap() {
    table = new Node *[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; ++i) { table[i] = nullptr; }
}

HashMap::HashMap(const HashMap &src) {
    table = new Node *[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) { table[i] = nullptr; }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *entry = src.table[i];
        while (entry != nullptr) {
            Node *newEntry = new Node(entry->value);
            newEntry->next = table[i];
            table[i] = newEntry;
            entry = entry->next;
        }
    }
}

HashMap &HashMap::operator=(const HashMap &src) {
    if (this == &src) { return *this; }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node *entry = table[i];
        while (entry != nullptr) {
            Node *prev = entry;
            entry = entry->next;
            delete prev;
        }
        table[i] = nullptr;
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node *entry = src.table[i];
        while (entry != nullptr) {
            Node *newEntry = new Node(entry->value);
            newEntry->next = table[i];
            table[i] = newEntry;
            entry = entry->next;
        }
    }
    return *this;
}

HashMap::~HashMap() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node *entry = table[i];
        while (entry != nullptr) {
            Node *prev = entry;
            entry = entry->next;
            delete prev;
        }
        table[i] = nullptr;
    }
    delete[] table;
}

unsigned long HashMap::hashCityName(MyString &name) {
    return hashCityName(name.getStr());
}

unsigned long HashMap::hashCityName(const char *name) {
    size_t hash;
    if (name[0] == '\0') return TABLE_SIZE - 1;
    else if (name[1] == '\0') {
        hash = name[0] * hashWeights[0];
    } else if (name[2] == '\0') {
        hash = name[0] * hashWeights[0] + name[1] * hashWeights[1];
    } else {
        hash = name[0] * hashWeights[0] + name[1] * hashWeights[1] + name[2] * hashWeights[2];
    }
    return hash % TABLE_SIZE;
}


City *HashMap::get(MyString &name) {
    unsigned long hash = HashMap::hashCityName(name);
    Node *entry = table[hash];

    while (entry != nullptr) {
        if (*(entry->value->name) == name) { return entry->value; }
        entry = entry->next;
    }
    return nullptr;
}

void HashMap::add(City *src) {
    unsigned long hash = HashMap::hashCityName(*(src->name));

    Node *current = this->table[hash];
    Node *previous = nullptr;

    while (current != nullptr) {
        if (*(current->value->name) == *(src->name)) {
            current->value = src;
            return;
        }
        previous = current;
        current = current->next;
    }

    current = new Node(src);
    if (previous == nullptr) { table[hash] = current; } // insert as first bucket
    else { previous->next = current; }
}

void HashMap::remove(MyString &name) {
    unsigned long hashValue = HashMap::hashCityName(name);
    Node *prev = nullptr;
    Node *current = table[hashValue];

    while (current != nullptr && *(current->value->name) != name) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) { return; } // key not found
    else {
        if (prev == nullptr) { table[hashValue] = current->next; } // remove first bucket of the list
        else { prev->next = current->next; }
        delete current;
    }
}