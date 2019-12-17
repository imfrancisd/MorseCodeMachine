#include "convertMorseFromRussian.h"
#include "../all/convertMorseFromRussian.h"
#include <Arduino.h>
#include <stddef.h>

int convertMorseFromRussian(const String &russianMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromRussian(russianMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromRussian(const String *russianMessage, char englishBuffer[], size_t englishBufferSize)
{
    if (russianMessage)
    {
        return convertMorseFromRussian(russianMessage->c_str(), englishBuffer, englishBufferSize);
    }
    return -1;
}

