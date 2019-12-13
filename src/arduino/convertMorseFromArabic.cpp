#include "convertMorseFromArabic.h"
#include "../all/convertMorseFromArabic.h"
#include <Arduino.h>
#include <stddef.h>

int convertMorseFromArabic(const String &arabicMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromArabic(arabicMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromArabic(const String *arabicMessage, char englishBuffer[], size_t englishBufferSize)
{
    if (arabicMessage)
    {
        return convertMorseFromArabic(arabicMessage->c_str(), englishBuffer, englishBufferSize);
    }
    return -1;
}

