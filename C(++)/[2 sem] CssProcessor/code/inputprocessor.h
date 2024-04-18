#ifndef BASIC_INPUTPROCESSOR_H
#define BASIC_INPUTPROCESSOR_H

#include "DoubleLinkedList.h"


class inputProcessor {
private:
    DoubleLinkedList *cssSections;
    bool selectorMode;
    bool propertyMode;
    bool valueMode;
    bool commandMode;
    bool workingStatus;
    char *input;

    void resetInput();

    void getDigitCommand();

    void getWordCommand();

    void readWord(CustomString *wordContainer, char separator);

    void readSelector(CustomString *wordContainer);

    bool checkModePattern(const char *singleChar) const;

    void checkMode();

    void processCommands();

    void processDataInput();

    void readProperty(CustomString *nameContainer, CustomString *valueContainer);

    void readProperties(CssSection *targetSection);

public:
    explicit inputProcessor(DoubleLinkedList *existingCssSections);

    inputProcessor(const inputProcessor &other);

    ~inputProcessor();

    inputProcessor &operator=(const inputProcessor &other);

    void getInput() const;

    void processInput();

    bool getWorkingStatus() const;
};


#endif //BASIC_INPUTPROCESSOR_H
