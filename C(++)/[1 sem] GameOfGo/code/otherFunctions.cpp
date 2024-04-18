#include <stdlib.h>
#include "otherFunctions.h"


short concatNumberFromCharArray(const char *charArray, int arrLen)
{
    int* numArray = (int*) calloc(arrLen, sizeof(int));
    int total = 0;

    for (int i = 0; i < arrLen; i++)
    {
        if (charArray[i] != '\0') numArray[i] = charArray[i] - '0';
        else numArray[i] = 10;
    }

    for (int x = 0; x < arrLen; x++)
    {
        if (numArray[x] < 10) total = (total * 10) + numArray[x];
    }

    free(numArray);

    return (short)total;
}


bool isCharNumber(const unsigned char character)
{
    return !(character == 0x30 ||
            character == 0x31 ||
            character == 0x32 ||
            character == 0x33 ||
            character == 0x34 ||
            character == 0x35 ||
            character == 0x36 ||
            character == 0x37 ||
            character == 0x38 ||
            character == 0x39 ||
            character == 0x0d);
}