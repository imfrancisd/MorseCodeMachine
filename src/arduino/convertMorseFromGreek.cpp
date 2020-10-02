#include "../all/convertMorseFromGreek.h"
#include "convertMorseFromGreek.h"

int convertMorseFromGreek(const String &greekMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromGreek(greekMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromGreek(const String *greekMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromGreek(greekMessage ? greekMessage->c_str() : nullptr, englishBuffer, englishBufferSize);
}

