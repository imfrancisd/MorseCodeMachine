#include "../all/convertMorseFromPersian.h"
#include "convertMorseFromPersian.h"

int convertMorseFromPersian(const String &persianMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromPersian(persianMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromPersian(const String *persianMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromPersian(persianMessage ? persianMessage->c_str() : nullptr, englishBuffer, englishBufferSize);
}

