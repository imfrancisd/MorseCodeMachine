#include "convertMorseFromPersian.h"
#include "../all/convertMorseFromPersian.h"
#include <Arduino.h>
#include <stddef.h>

int convertMorseFromPersian(const String &persianMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromPersian(persianMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromPersian(const String *persianMessage, char englishBuffer[], size_t englishBufferSize)
{
    if (persianMessage)
    {
        return convertMorseFromPersian(persianMessage->c_str(), englishBuffer, englishBufferSize);
    }
    return -1;
}

