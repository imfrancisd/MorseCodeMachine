#include "../all/convertMorseFromHebrew.h"
#include "convertMorseFromHebrew.h"
#include <Arduino.h>
#include <stddef.h>

int convertMorseFromHebrew(const String &hebrewMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromHebrew(hebrewMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromHebrew(const String *hebrewMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromHebrew(hebrewMessage ? hebrewMessage->c_str() : nullptr, englishBuffer, englishBufferSize);
}

