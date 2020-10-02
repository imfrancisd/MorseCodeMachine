#include "../all/convertMorseFromRussian.h"
#include "convertMorseFromRussian.h"

int convertMorseFromRussian(const String &russianMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromRussian(russianMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromRussian(const String *russianMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromRussian(russianMessage ? russianMessage->c_str() : nullptr, englishBuffer, englishBufferSize);
}

