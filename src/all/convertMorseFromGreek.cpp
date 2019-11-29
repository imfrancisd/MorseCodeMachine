#include "convertMorseFromGreek.h"
#include "_enToMorseElements.h"
#include "_isDiacritic.h"
#include "_skipDiacritic.h"
#include <stddef.h>
#include <string.h>

int convertMorseFromGreek(const char greekMessage[], char englishBuffer[], size_t englishBufferSize)
{
    if (!(greekMessage && englishBuffer && (englishBufferSize >= 1)))
    {
        return -1;
    }

    char *destination = englishBuffer;
    char *destinationEnd = englishBuffer + englishBufferSize;
    const char *source = greekMessage;
    const char *sourceEnd = greekMessage;

    while (*source)
    {
        if (_enToMorseElements(&sourceEnd))
        {
            size_t countBytes = sourceEnd - source;
            memcpy(destination, source, countBytes);
            destination += countBytes;
            source = sourceEnd;
        }

        //TODO: The rest of the function.
    }

    if (destination >= destinationEnd)
    {
        destinationEnd[- 1] = '\0';
        return 1;
    }

    *destination = '\0';
    return 0;
}

