#ifndef TEST_MYSTRING_H
#define TEST_MYSTRING_H

#include "iostream"

class MyString {
private:
    char *str;
    int length;
    int buffer;
public:
    MyString();

    explicit MyString(const char *initChars);

    MyString(const MyString &other);

    ~MyString();

    int getLength() const;

    const char *getStr() const;

    MyString &operator=(const MyString &other);

    MyString &operator=(char *newStr);

    bool operator==(const MyString &other) const;

    bool operator==(const char *compStr) const;

    bool operator!=(const MyString &other) const;

    bool operator!=(const char *compStr) const;

    MyString operator+(const MyString &other);

    MyString operator+(const char *newStr);

    MyString &operator+=(const MyString &other);

    MyString &operator+=(char *newStr);

    MyString &operator+=(char &letter);

    char &operator[](int index);

    const char &operator[](int index) const;

    friend std::ostream &operator<<(std::ostream &os, const MyString &string);

    friend std::istream &operator>>(std::istream &is, MyString &string);

    friend MyString operator+(char *str, const MyString &other);

    void clear();

protected:
    friend bool strCmp(const char *str1, const char *str2);

    friend int strLen(const char *str);

    friend void strCopy(char *dest, const char *src);

    friend void strCat(char *dest, const char *src);

    void copyObj(const MyString &other);

    void copy(const char *string);

    void setLength(int newLength);

    void setStr(const char *newStr);
};

#endif //TEST_MYSTRING_H
