#ifndef BASIC_CUSTOMSTRING_H
#define BASIC_CUSTOMSTRING_H

#include "iostream"

class CustomString {
private:
    char *str;
    int length;
    int buffer;
public:
    CustomString();

    explicit CustomString(const char *initChars);

    CustomString(const CustomString &other);

    ~CustomString();

    int getLength() const;

    const char *getStr() const;

    void removeSpace();

    CustomString &operator=(const CustomString &other);

    CustomString &operator=(char *newStr);

    bool operator==(const CustomString &other) const;

    bool operator==(const char *compStr) const;

    bool operator!=(const CustomString &other) const;

    bool operator!=(const char *compStr) const;

    CustomString operator+(const CustomString &other);

    CustomString operator+(const char *newStr);

    CustomString &operator+=(const CustomString &other);

    CustomString &operator+=(char *newStr);

    char &operator[](int index);

    const char &operator[](int index) const;

    friend std::ostream &operator<<(std::ostream &os, const CustomString &string);

    friend std::istream &operator>>(std::istream &is, CustomString &string);

    friend CustomString operator+(char *str, const CustomString &other);

    friend bool isWhiteSpace(char c);

protected:
    friend bool strCmp(const char *str1, const char *str2);

    friend int strLen(const char *str);

    friend void strCopy(char *dest, const char *src);

    friend void strCat(char *dest, const char *src);

    void copyObj(const CustomString &other);

    void copy(const char *string);

    void clear();

    void setLength(int newLength);

    void setStr(const char *newStr);

    void removeSpaceAtTheEnd();

    void removeSpaceAtTheBeginning();
};

bool isWhiteSpace(char c);

#endif //BASIC_CUSTOMSTRING_H
