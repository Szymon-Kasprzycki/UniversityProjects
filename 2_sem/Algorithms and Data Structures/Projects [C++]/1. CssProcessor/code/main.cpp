#include <iostream>
#include "DoubleLinkedList.h"
#include "CustomString.h"
#include "inputProcessor.h"
#define T 8

using namespace std;

int main() {
    auto* list = new DoubleLinkedList(T);
    auto* processor = new inputProcessor(list);
    while (processor->getWorkingStatus())
    {
        processor->getInput();
        processor->processInput();
    }
    delete processor;
    delete list;
    return 0;
}
