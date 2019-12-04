#include "convertMorseFromGreek.h"
#include "../all/convertMorseFromGreek.h"
#include <Arduino.h>
#include <stddef.h>

int convertMorseFromGreek(const String &greekMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromGreek(greekMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromGreek(const String *greekMessage, char englishBuffer[], size_t englishBufferSize)
{
    if (greekMessage)
    {
        return convertMorseFromGreek(greekMessage->c_str(), englishBuffer, englishBufferSize);
    }
    return -1;
}

