#include <iostream>
#include "mapInputProcessor.h"

int main() {
    auto* processor = new mapInputProcessor();
    processor->processInput();
    processor->processCommands();
    delete processor;
    return 0;
}
