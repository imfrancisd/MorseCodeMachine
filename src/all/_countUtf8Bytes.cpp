#include "_countUtf8Bytes.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



unsigned char _countUtf8Bytes(const char *bytes)
{
    if ((bytes[0] & 0b10000000) == 0)
    {
        //Found ascii character.
        return 1;
    }

    if (((bytes[0] & 0b11100000) == 0b11000000) &&
        ((bytes[1] & 0b11000000) == 0b10000000))
    {
        //Found 2 byte UTF-8 character.
        return 2;
    }

    if (((bytes[0] & 0b11110000) == 0b11100000) &&
        ((bytes[1] & 0b11000000) == 0b10000000) &&
        ((bytes[2] & 0b11000000) == 0b10000000))
    {
        //Found 3 byte UTF-8 character.
        return 3;
    }

    if (((bytes[0] & 0b11111000) == 0b11110000) &&
        ((bytes[1] & 0b11000000) == 0b10000000) &&
        ((bytes[2] & 0b11000000) == 0b10000000) &&
        ((bytes[3] & 0b11000000) == 0b10000000))
    {
        //Found 4 byte UTF-8 character.
        return 4;
    }

    //Found extended ascii character or error in UTF-8 encoding.
    return 0;
}

