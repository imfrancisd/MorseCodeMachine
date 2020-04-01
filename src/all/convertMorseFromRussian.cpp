#include "_countUtf8Bytes.h"
#include "_enFromRussianMorse.h"
#include "_enToMorseElements.h"
#include "_skipDiacritic.h"
#include "_writeUnicodeFFFD.h"
#include "convertMorseFromRussian.h"
#include <string.h>

using namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795;

static int convertMorseFromRussian(const unsigned char russianMessage[], unsigned char englishBuffer[], size_t englishBufferSize)
{
    if (!(russianMessage && englishBuffer && (englishBufferSize >= 1)))
    {
        return -1;
    }

    unsigned char *destination = englishBuffer;
    unsigned char *destinationEnd = destination + englishBufferSize;
    const unsigned char *source = russianMessage;
    const unsigned char *sourceReset = source;

    while (*source)
    {
        //=====================================================================
        //Translate Russian characters.
        //=====================================================================

        if (_enFromRussianMorse(&source, &destination, destinationEnd) == 1)
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

int convertMorseFromRussian(const char russianMessage[], char englishBuffer[], size_t englishBufferSize)
{
    return convertMorseFromRussian(reinterpret_cast<const unsigned char *>(russianMessage), reinterpret_cast<unsigned char *>(englishBuffer), englishBufferSize);
}

