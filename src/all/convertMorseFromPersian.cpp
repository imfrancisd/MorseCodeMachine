#include "_countUtf8Bytes.h"
#include "_enFromPersianMorse.h"
#include "_enToMorseElements.h"
#include "_skipDiacritic.h"
#include "_writeUnicodeFFFD.h"
#include "convertMorseFromPersian.h"
#include <string.h>

using namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795;

static int convertMorseFromPersian(const unsigned char persianMessage[], unsigned char englishBuffer[], size_t englishBufferSize)
{
    if (!(persianMessage && englishBuffer && (englishBufferSize >= 1)))
    {
        return -1;
    }

    unsigned char *destination = englishBuffer;
    unsigned char *destinationEnd = destination + englishBufferSize;
    const unsigned char *source = persianMessage;
    const unsigned char *sourceReset = source;

    while (*source)
    {
        //=====================================================================
        //Translate Persian characters.
        //=====================================================================

        if (_enFromPersianMorse(&source, &destination, destinationEnd) == 1)
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

int convertMorseFromPersian(const char persianMessage[], char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromPersian(reinterpret_cast<const unsigned char *>(persianMessage), reinterpret_cast<unsigned char *>(englishBuffer), englishBufferSize);
}

