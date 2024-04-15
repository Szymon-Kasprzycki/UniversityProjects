#ifndef BASIC_CSSSECTION_H
#define BASIC_CSSSECTION_H

#include "SelectorList.h"
#include "AttributeList.h"

class CssSection {
private:
    AttributeList *properties;
    SelectorList *selectors;
public:
    CssSection();

    CssSection(const CssSection &other);

    ~CssSection();

    CssSection &operator=(const CssSection &other);

    void addSelector(CustomString *selector);

    void addAttribute(CustomString *property, CustomString *value);

    CustomString *getSelector(int index);

    CustomString *getSelector(CustomString *selector);

    CustomString *getAttribute(CustomString *property);

    bool removeAttribute(CustomString *property);

    void setAttribute(CustomString *property, CustomString *value);

    int getSelectorsCount() const;

    int getAttributesCount() const;

    void clear();

    bool isEmpty() const;

protected:
    void copy(const CssSection &other);

    int getIndexOfSelector(CustomString *selector) const;
};


#endif //BASIC_CSSSECTION_H
