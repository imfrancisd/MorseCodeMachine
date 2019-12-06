#include "convertMorseFromHebrew.h"
#include "../all/convertMorseFromHebrew.h"
#include <Arduino.h>
#include <stddef.h>

int convertMorseFromHebrew(const String &hebrewMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromHebrew(hebrewMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromHebrew(const String *hebrewMessage, char englishBuffer[], size_t englishBufferSize)
{
    if (hebrewMessage)
    {
        return convertMorseFromHebrew(hebrewMessage->c_str(), englishBuffer, englishBufferSize);
    }
    return -1;
}

