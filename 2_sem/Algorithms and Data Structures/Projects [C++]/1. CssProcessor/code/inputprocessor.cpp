#include "inputProcessor.h"
#include "iostream"

using namespace std;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

CustomString *resetContainer(CustomString *container) {
    container = new CustomString();
    return container;
}

inputProcessor::inputProcessor(DoubleLinkedList *existingCssSections) {
    this->cssSections = existingCssSections;
    this->input = new char[2];
    this->input[1] = '\0';
    this->selectorMode = true;
    this->propertyMode = false;
    this->valueMode = false;
    this->commandMode = false;
    this->workingStatus = true;
}

inputProcessor::inputProcessor(const inputProcessor &other) {
    this->cssSections = other.cssSections;
    this->input = new char[2];
    this->input[1] = '\0';
    this->selectorMode = other.selectorMode;
    this->propertyMode = other.propertyMode;
    this->valueMode = other.valueMode;
    this->commandMode = other.commandMode;
    this->workingStatus = other.workingStatus;
}

inputProcessor::~inputProcessor() {
    delete[] this->input;
}

void inputProcessor::getInput() const {
    this->input[0] = (char) getchar();
}

void inputProcessor::processInput() {
    if (this->input[0] == EOF) {
        this->workingStatus = false;
        return;
    }
    if (this->input[0] == '\n' || this->input[0] == '\t') return;
    this->checkMode();
    if (this->commandMode) this->processCommands();
    else this->processDataInput();
}

void inputProcessor::checkMode() {
    if (!this->commandMode && checkModePattern("?")) {
        this->resetInput();
        this->commandMode = true;
    } else if (this->commandMode && checkModePattern("*")) {
        this->resetInput();
        this->commandMode = false;
    }
}

bool inputProcessor::checkModePattern(const char *singleChar) const {
    char c[3] = {'\0', '\0', '\0'};
    bool isPattern = true;
    if (this->input[0] == *singleChar) {
        for (int i = 0; i < 3; i++) {
            c[i] = (char) getchar();
            if (i == EOF) isPattern = false;
        }
        for (char i: c) if (i != *singleChar) isPattern = false;
    } else isPattern = false;
    if (!isPattern) {
        // Return input to stdin if pattern is not found
        for (int i = 2; i >= 0; i--) {
            if (c[i] == EOF) return isPattern;
            if (c[i] != '\0') ungetc(c[i], stdin);
        }
    }
    return isPattern;
}

bool inputProcessor::getWorkingStatus() const { return workingStatus; }

void inputProcessor::processCommands() {
    if (this->input[0] == '\0') return;
    if (this->input[0] == '?') cout << "? == " << this->cssSections->getSize() << endl;
    else if (isDigit(this->input[0])) this->getDigitCommand();
    else if (!isDigit(this->input[0])) this->getWordCommand();
}

void inputProcessor::resetInput() { this->input[0] = '\0'; }

void inputProcessor::getDigitCommand() {
    ungetc(this->input[0], stdin);
    int sectionIndex;
    char commandType;
    scanf_s("%d,%c,", &sectionIndex, &commandType, 1);
    switch (commandType) {
        case 'D':
            this->getInput();
            if (this->input[0] == '*') {
                int status = this->cssSections->removeCssSection(sectionIndex);
                if (status) std::cout << sectionIndex << "," << commandType << ",*" << " == deleted" << std::endl;
            } else {
                CustomString attribute;
                this->readWord(&attribute, '\n');
                int status = this->cssSections->removeAttributeFromSectionIndex(sectionIndex, &attribute);
                if (status) {
                    std::cout << sectionIndex << "," << commandType << "," << attribute << " == deleted" << std::endl;
                }
            }
            break;
        case 'S': // Print selector or number of selectors
            this->getInput();
            if (isDigit(this->input[0])) {
                int selectorIndex = int(this->input[0]) - '0' - 1;
                CssSection *target = this->cssSections->getCssSection(sectionIndex);
                if (target == nullptr) return;
                CustomString *selector = target->getSelector(selectorIndex);
                if (selector == nullptr) return;
                cout << sectionIndex << "," << commandType << "," << selectorIndex + 1 << " == " << *selector << endl;
            } else if (this->input[0] == '?') {
                CssSection *target = this->cssSections->getCssSection(sectionIndex);
                if (target != nullptr) {
                    const int selectorsCount = target->getSelectorsCount();
                    cout << sectionIndex << "," << commandType << "," << "?" << " == " << selectorsCount << endl;
                }
            }
            break;
        case 'A':
            this->getInput();
            if (this->input[0] == '?') {
                CssSection *target = this->cssSections->getCssSection(sectionIndex);
                if (target == nullptr) return;
                const int attributesCount = target->getAttributesCount();
                cout << sectionIndex << "," << commandType << "," << "?" << " == " << attributesCount << endl;
            } else {
                CustomString attribute;
                this->readWord(&attribute, '\n');
                CssSection *target = this->cssSections->getCssSection(sectionIndex);
                if (target == nullptr) return;
                CustomString *value = target->getAttribute(&attribute);
                if (value == nullptr) return;
                else cout << sectionIndex << "," << commandType << "," << attribute << " == " << *value << endl;
            }
            break;
        default:
            // Invalid command - do nothing
            break;
    }
}

void inputProcessor::getWordCommand() {
    CustomString word;
    CustomString commandType;
    this->readWord(&word, ',');
    this->getInput();
    this->readWord(&commandType, ',');
    if (commandType.getLength() != 1) return; // When command type is not a single character
    switch (commandType[0]) {
        case 'A': {
            this->getInput();
            if (this->input[0] == '?') {
                int count = this->cssSections->getPropertiesCount(word);
                std::cout << word << "," << commandType[0] << "," << "?" << " == " << count << std::endl;
                return;
            }
            break;
        }
        case 'S': {
            this->getInput();
            if (this->input[0] == '?') {
                int count = this->cssSections->getSelectorsCount(word);
                std::cout << word << "," << commandType[0] << "," << "?" << " == " << count << std::endl;
            }
            break;
        }
        case 'E': {
            CustomString attribute;
            this->readWord(&attribute, '\n');
            CustomString *value = this->cssSections->getSelectorAttributeValue(word, attribute);
            if (value == nullptr) return;
            else std::cout << word << "," << commandType[0] << "," << attribute << " == " << *value << std::endl;
            break;
        }
        default:
            // when command type is not valid do nothing
            break;
    }
}

void inputProcessor::readWord(CustomString *wordContainer, char separator) {
    *wordContainer += this->input;
    this->resetInput();
    char *c = new char[2];
    c[1] = '\0';
    while (true) {
        *c = (char) getchar();
        if (*c == EOF || *c == separator || *c == '\n') break;
        else if (*c == '\t') continue;
        *wordContainer += c;
    }
    wordContainer->removeSpace();
    delete[] c;
}

void inputProcessor::readSelector(CustomString *wordContainer) {
    // Handle empty selector
    if (this->input[0] == '{') {
        this->selectorMode = false;
        this->propertyMode = true;
        this->resetInput();
        return;
    }
    *wordContainer += this->input;
    this->resetInput();
    char *c = new char[2];
    c[1] = '\0';
    while (true) {
        *c = (char) getchar();
        if (*c == ',') break;
        else if (*c == '{') {
            this->selectorMode = false;
            this->propertyMode = true;
            break;
        } else if (*c == '\n' || *c == '\t' || *c == '\0') continue;
        *wordContainer += c;
    }
    wordContainer->removeSpace();
    delete[] c;
}

void inputProcessor::readProperty(CustomString *nameContainer, CustomString *valueContainer) {
    *nameContainer += this->input;
    this->resetInput();
    char *c = new char[2];
    c[1] = '\0';
    while (true) {
        *c = (char) getchar();
        if (*c == ':') {
            this->valueMode = true;
            *c = (char) getchar();
            if (*c != ' ') ungetc(*c, stdin);
            continue;
        } else if (*c == ';') {
            this->valueMode = false;
            break;
        } else if (*c == '}') {
            this->valueMode = false;
            this->propertyMode = false;
            break;
        } else if ((!this->valueMode && *c == ' ') || *c == '\n' || *c == '\t') continue;
        // Check where to put the character and put it
        if (this->valueMode) *valueContainer += c;
        else *nameContainer += c;
    }
    delete[] c;
}

void inputProcessor::readProperties(CssSection *targetSection) {
    auto *name = new CustomString();
    auto *value = new CustomString();
    int status = 1;
    while (this->propertyMode) {
        readProperty(name, value);
        if (name->getLength() == 0 || value->getLength() == 0) status = 0;
        if (status) {
            if (targetSection->getAttribute(name) == nullptr) {
                targetSection->addAttribute(name, value);
                name = resetContainer(name);
                value = resetContainer(value);
            } else {
                targetSection->setAttribute(name, value);
                name = resetContainer(name);
                value = resetContainer(value);

            }
            continue;
        }
        name = resetContainer(name);
        value = resetContainer(value);
        status = 1;
    }
    this->propertyMode = true;
}

void inputProcessor::processDataInput() {
    if (this->input[0] == '\0') return;
    auto *section = new CssSection();
    auto *container = new CustomString();
    while (this->selectorMode) {
        this->readSelector(container);
        if (container->getLength() == 0) break;
        section->addSelector(container);
        container = resetContainer(container);
    }
    delete container;
    this->selectorMode = true;
    readProperties(section);
    this->cssSections->addCssSection(section);
}

inputProcessor &inputProcessor::operator=(const inputProcessor &other) {
    if (this != &other) {
        this->input = other.input;
        this->selectorMode = other.selectorMode;
        this->propertyMode = other.propertyMode;
        this->valueMode = other.valueMode;
        this->cssSections = other.cssSections;
        this->commandMode = other.commandMode;
        this->workingStatus = other.workingStatus;
    }
    return *this;
}