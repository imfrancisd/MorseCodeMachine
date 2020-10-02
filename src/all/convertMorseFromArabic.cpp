#include "_countUtf8Bytes.h"
#include "_enFromArabicMorse.h"
#include "_enToMorseElements.h"
#include "_skipDiacritic.h"
#include "_writeUnicodeFFFD.h"
#include "convertMorseFromArabic.h"
#include <string.h>

using namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795;

static int convertMorseFromArabic(const unsigned char arabicMessage[], unsigned char englishBuffer[], size_t englishBufferSize)
{
    if (!(arabicMessage && englishBuffer && (englishBufferSize >= 1)))
    {
        return -1;
    }

    unsigned char *destination = englishBuffer;
    unsigned char *destinationEnd = destination + englishBufferSize;
    const unsigned char *source = arabicMessage;
    const unsigned char *sourceReset = source;

    while (*source)
    {
        //=====================================================================
        //Translate Arabic characters.
        //=====================================================================

        if (_enFromArabicMorse(&source, &destination, destinationEnd) == 1)
        {
            //Not enough space to translate.
            *destination = 0x00;
            return 1;
        }
        else if (sourceReset != source)
        {
            //Translation successful.
            sourceReset = source;
            continue;
        }
        else
        {
            //Reset.
            source = sourceReset;
        }

        //=====================================================================
        //Translate English letters, digits, and symbols defined by Morse code.
        //=====================================================================

        if (_enToMorseElements(&source))
        {
            size_t countBytes = source - sourceReset;
            if (destinationEnd <= destination + countBytes)
            {
                //Not enough space to translate.
                *destination = 0x00;
                return 1;
            }
            memcpy(destination, sourceReset, countBytes);
            destination += countBytes;

            //Translation successful.
            sourceReset = source;
            continue;
        }
        else
        {
            //Reset.
            source = sourceReset;
        }

        //=====================================================================
        //Unknown character.
        //=====================================================================

        unsigned char countUtf8Bytes = _countUtf8Bytes(source);

        //Go to next UTF-8 character.
        source += (countUtf8Bytes > 0) ? countUtf8Bytes : 1;

        //Skip diacritics only if valid UTF-8 character found.
        if (countUtf8Bytes > 0)
        {
            while (_skipDiacritic(&source))
                ;
        }

        //Translate unknown character to U+FFFD.
        if (!_writeUnicodeFFFD(&destination, destinationEnd))
        {
            //Not enough space to translate.
            *destination = 0x00;
            return 1;
        }
        else
        {
            //Translation successful.
            sourceReset = source;
            continue;
        }
    }

    *destination = 0x00;
    return 0;
}

int convertMorseFromArabic(const char arabicMessage[], char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromArabic(reinterpret_cast<const unsigned char *>(arabicMessage), reinterpret_cast<unsigned char *>(englishBuffer), englishBufferSize);
}

