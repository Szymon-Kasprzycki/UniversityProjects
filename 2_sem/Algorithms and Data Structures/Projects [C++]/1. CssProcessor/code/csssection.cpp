#include "CssSection.h"
#include "AttributeList.h"

CssSection::CssSection() {
    this->selectors = new SelectorList();
    this->properties = new AttributeList();
}

CssSection::CssSection(const CssSection &other) {
    this->selectors = new SelectorList();
    this->properties = new AttributeList();
    this->copy(other);
}

CssSection::~CssSection() {
    delete this->selectors;
    delete this->properties;
}

void CssSection::addSelector(CustomString *selector) {
    this->selectors->pushBack(selector);
}

void CssSection::addAttribute(CustomString *property, CustomString *value) {
    this->properties->insert(property, value);
}

bool CssSection::removeAttribute(CustomString *property) {
    // Status is true if the property was found and removed else false
    int status = this->properties->remove(property);
    return status;
}

void CssSection::clear() {
    this->selectors->clear();
    this->properties->clear();
}

int CssSection::getSelectorsCount() const {
    return this->selectors->getSize();
}

int CssSection::getAttributesCount() const {
    return this->properties->getSize();
}

bool CssSection::isEmpty() const {
    return this->properties->isEmpty();
}

CustomString *CssSection::getSelector(int index) {
    return this->selectors->get(index);
}

CustomString *CssSection::getSelector(CustomString *selector) {
    int index = this->getIndexOfSelector(selector);
    if (index != -1) return this->selectors->get(index);
    else return nullptr;
}

CustomString *CssSection::getAttribute(CustomString *property) {
    CustomString *value = this->properties->get(property);
    return value;
}

void CssSection::setAttribute(CustomString *property, CustomString *value) {
    this->properties->setValue(property, value);
}

int CssSection::getIndexOfSelector(CustomString *selector) const {
    return this->selectors->getIndexOf(selector);
}

void CssSection::copy(const CssSection &other) {
    this->selectors->copy(*(other.selectors));
    this->properties->copy(*(other.properties));
}

CssSection &CssSection::operator=(const CssSection &other) {
    if (this != &other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}