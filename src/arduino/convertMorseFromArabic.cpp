#include "../all/convertMorseFromArabic.h"
#include "convertMorseFromArabic.h"

int convertMorseFromArabic(const String &arabicMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromArabic(arabicMessage.c_str(), englishBuffer, englishBufferSize);
}

int convertMorseFromArabic(const String *arabicMessage, char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromArabic(arabicMessage ? arabicMessage->c_str() : nullptr, englishBuffer, englishBufferSize);
}

