#define strBuffer 8

#include "CustomString.h"

bool isWhiteSpace(char c) {
    return c == '\n' || c == '\t' || c == '\r' || c == ' ' || c == '\0';
}

int strLen(const char *str) {
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

void strCopy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void strCat(char *dest, const char *src) {
    while (*dest != '\0') dest++;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

bool strCmp(const char *str1, const char *str2) {
    if (strLen(str1) != strLen(str2)) return false;
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) return false;
        str1++;
        str2++;
    }
    return true;
}

CustomString::CustomString() {
    this->str = new char[strBuffer];
    this->str[0] = '\0';
    this->length = 0;
    this->buffer = strBuffer;
}

CustomString::CustomString(const char *initChars) {
    this->copy(initChars);
}

CustomString::CustomString(const CustomString &other) {
    this->copyObj(other);
}

CustomString::~CustomString() {
    this->clear();
}

void CustomString::setLength(int newLength) {
    this->length = newLength;
}

int CustomString::getLength() const {
    return this->length;
}

const char *CustomString::getStr() const {
    return this->str;
}

void CustomString::setStr(const char *newStr) {
    this->copy(newStr);
}

CustomString &CustomString::operator=(const CustomString &other) {
    if (this != &other) this->copyObj(other);
    return *this;
}

CustomString &CustomString::operator=(char *newStr) {
    this->copy(newStr);
    return *this;
}

bool CustomString::operator==(const CustomString &other) const {
    return strCmp(this->str, other.str);
}

bool CustomString::operator==(const char *compStr) const {
    return strCmp(this->str, compStr);
}

bool CustomString::operator!=(const CustomString &other) const {
    return *this->str != *other.getStr();
}

bool CustomString::operator!=(const char *compStr) const {
    return *this->str != *compStr;
}

CustomString CustomString::operator+(const CustomString &other) {
    *this = *this + other.str;
    return *this;
}

CustomString CustomString::operator+(const char *newStr) {
    CustomString result;
    result.length = this->length + strLen(newStr);
    result.buffer = result.length - (result.length % strBuffer) + strBuffer;
    result.str = new char[result.buffer];
    strCopy(result.str, this->str);
    strCat(result.str, newStr);
    return result;
}

CustomString &CustomString::operator+=(const CustomString &other) {
    *this = *this + other.getStr();
    return *this;
}

CustomString &CustomString::operator+=(char *newStr) {
    int newLength = this->length + strLen(newStr);
    if (newLength >= this->buffer) {
        this->length = newLength;
        this->buffer = newLength - (newLength % strBuffer) + strBuffer;
        char *temp = new char[this->buffer];
        strCopy(temp, this->str);
        strCat(temp, newStr);
        delete[] this->str;
        this->str = temp;
    } else {
        this->length = newLength;
        strCat(this->str, newStr);
    }
    return *this;
}

char &CustomString::operator[](int index) {
    if (index >= this->length) return this->str[this->length - 1];
    return this->str[index];
}

const char &CustomString::operator[](int index) const {
    if (index >= this->length) return this->str[this->length - 1];
    return this->str[index];
}

std::ostream &operator<<(std::ostream &os, const CustomString &string) {
    os << string.str;
    return os;
}

std::istream &operator>>(std::istream &is, CustomString &string) {
    char *buffer = new char[1000];
    is >> buffer;
    string = buffer;
    delete[] buffer;
    return is;
}

CustomString operator+(char *str, const CustomString &other) {
    CustomString result;
    int size = strLen(str) + other.getLength();
    result.buffer = size - (size % strBuffer) + strBuffer;
    result.setLength(size);
    strCat(str, other.getStr());
    result.setStr(str);
    return result;
}

void CustomString::copyObj(const CustomString &other) {
    this->copy(other.str);
}

void CustomString::copy(const char *string) {
    this->clear();
    this->length = strLen(string);
    this->buffer = this->length - (this->length % strBuffer) + strBuffer;
    this->str = new char[this->buffer];
    strCopy(this->str, string);
}

void CustomString::clear() {
    delete[] this->str;
    this->str = nullptr;
    this->length = 0;
    this->buffer = strBuffer;
}

void CustomString::removeSpaceAtTheEnd() {
    if (this->length == 0) return;
    int i = this->length - 1;
    while (isWhiteSpace(this->str[i])) {
        this->str[i] = '\0';
        i--;
    }
    this->length = i + 1;
}

void CustomString::removeSpaceAtTheBeginning() {
    if (this->length == 0) return;
    int i = 0;
    while (isWhiteSpace(this->str[i])) i++;
    int j = 0;
    while (this->str[i] != '\0') {
        this->str[j] = this->str[i];
        i++;
        j++;
    }
    this->str[j] = '\0';
    this->length = j;
}

void CustomString::removeSpace() {
    this->removeSpaceAtTheEnd();
    this->removeSpaceAtTheBeginning();
}