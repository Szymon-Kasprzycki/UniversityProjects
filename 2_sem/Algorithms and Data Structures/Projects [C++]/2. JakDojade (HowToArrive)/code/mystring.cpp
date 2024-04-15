#include "MyString.h"
#include "iostream"

#define strBuffer 7

using namespace std;

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
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return true;
}

MyString::MyString() {
    this->str = new char[strBuffer];
    this->str[0] = '\0';
    this->length = 0;
    this->buffer = strBuffer;
}

MyString::MyString(const char *initChars) {
    this->copy(initChars);
}

MyString::MyString(const MyString &other) {
    this->copyObj(other);
}

MyString::~MyString() {
    this->clear();
    delete[] this->str;
}

void MyString::setLength(int newLength) {
    this->length = newLength;
}

int MyString::getLength() const {
    return this->length;
}

const char *MyString::getStr() const {
    return this->str;
}

void MyString::setStr(const char *newStr) {
    this->copy(newStr);
}

MyString &MyString::operator=(const MyString &other) {
    if (this != &other) this->copyObj(other);
    return *this;
}

MyString &MyString::operator=(char *newStr) {
    this->copy(newStr);
    return *this;
}

bool MyString::operator==(const MyString &other) const {
    return strCmp(this->str, other.str);
}

bool MyString::operator==(const char *compStr) const {
    return strCmp(this->str, compStr);
}

bool MyString::operator!=(const MyString &other) const {
    return *this->str != *other.getStr();
}

bool MyString::operator!=(const char *compStr) const {
    return *this->str != *compStr;
}

MyString MyString::operator+(const MyString &other) {
    *this = *this + other.str;
    return *this;
}

MyString MyString::operator+(const char *newStr) {
    MyString result;
    result.length = this->length + strLen(newStr);
    result.buffer = result.length - (result.length % strBuffer) + strBuffer;
    result.str = new char[result.buffer];
    strCopy(result.str, this->str);
    strCat(result.str, newStr);
    return result;
}

MyString &MyString::operator+=(const MyString &other) {
    *this = *this + other.getStr();
    return *this;
}

MyString &MyString::operator+=(char *newStr) {
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

MyString &MyString::operator+=(char &letter) {
    int newLength = this->length + 1;
    char newStr[2] = {letter, '\0'};
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

char &MyString::operator[](int index) {
    if (index >= this->length) return this->str[this->length - 1];
    return this->str[index];
}

const char &MyString::operator[](int index) const {
    if (index >= this->length) return this->str[this->length - 1];
    return this->str[index];
}

std::ostream &operator<<(std::ostream &os, const MyString &string) {
    os << string.str;
    return os;
}

std::istream &operator>>(std::istream &is, MyString &string) {
    char *buffer = new char[1000];
    is >> buffer;
    string = buffer;
    delete[] buffer;
    return is;
}

MyString operator+(char *str, const MyString &other) {
    MyString result;
    int size = strLen(str) + other.getLength();
    result.buffer = size - (size % strBuffer) + strBuffer;
    result.setLength(size);
    strCat(str, other.getStr());
    result.setStr(str);
    return result;
}

void MyString::copyObj(const MyString &other) {
    this->copy(other.str);
}

void MyString::copy(const char *string) {
    this->clear();
    this->length = strLen(string);
    this->buffer = this->length - (this->length % strBuffer) + strBuffer;
    this->str = new char[this->buffer];
    strCopy(this->str, string);
}

void MyString::clear() {
    delete[] this->str;
    this->str = new char[strBuffer];
    this->length = 0;
    this->buffer = strBuffer;
}