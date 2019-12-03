#include "_countUtf8Bytes.h"
#include "_enToMorseElements.h"
#include "_isDiacritic.h"
#include "_skipDiacritic.h"
#include "_writeUnicodeFFFD.h"
#include "convertMorseFromGreek.h"
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
        //Read English letters, digits, and symbols defined by Morse code.

        if (_enToMorseElements(&sourceEnd))
        {
            size_t countBytes = sourceEnd - source;
            if (destinationEnd <= destination + countBytes)
            {
                destination[0] = '\0';
                return 1;
            }
            memcpy(destination, source, countBytes);
            destination += countBytes;
            source = sourceEnd;

            continue;
        }

        //Reset.
        sourceEnd = source;

        //Read Greek letters defined in Greek Morse code.
        //Greek and Coptic characters are from U+0370 to U+03FF (2 bytes in UTF-8).
        //Not translating any character followed by diacritics.

        unsigned char countUtf8Bytes = _countUtf8Bytes(sourceEnd);

        if ((countUtf8Bytes != 2) || (_isDiacritic(sourceEnd)) || _isDiacritic(sourceEnd + 2))
        {
            //Not Greek character, a diacritic, or a character followed by diacritics.
            //Replace with U+FFFD (3 byte UTF-8 character).
            if (!_writeUnicodeFFFD(&destination, destinationEnd))
            {
                *destination = '\0';
                return 1;
            }

            //Skip character.
            if (countUtf8Bytes == 0)
            {
                //Skip invalid byte.
                sourceEnd += 1;
            }
            else if (_isDiacritic(sourceEnd))
            {
                //Skip diacritic (diacritic not preceded by character).
                sourceEnd += countUtf8Bytes;
            }
            else
            {
                //Skip character followed by diacritics.
                sourceEnd += countUtf8Bytes;
                while (_skipDiacritic(&sourceEnd))
                    ;
            }
            source = sourceEnd;

            continue;
        }

        //Translate Greek characters.

        if (destinationEnd <= destination + 1)
        {
            //No point in translating if there is no room in destination.
            *destination = '\0';
            return 1;
        }

        if (sourceEnd[0] == '\xce')
        {
            switch (sourceEnd[1])
            {
                case '\x91': //Α
                case '\xb1': //α
                    *destination++ = 'A';
                    break;

                case '\x92': //Β
                case '\xb2': //β
                    *destination++ = 'B';
                    break;

                case '\x93': //Γ
                case '\xb3': //γ
                    *destination++ = 'G';
                    break;

                case '\x94': //Δ
                case '\xb4': //δ
                    *destination++ = 'D';
                    break;

                case '\x95': //Ε
                case '\xb5': //ε
                    *destination++ = 'E';
                    break;

                case '\x96': //Ζ
                case '\xb6': //ζ
                    *destination++ = 'Z';
                    break;

                case '\x97': //Η
                case '\xb7': //η
                    *destination++ = 'H';
                    break;

                case '\x98': //Θ
                case '\xb8': //θ
                    *destination++ = 'C';
                    break;

                case '\x99': //Ι
                case '\xb9': //ι
                    *destination++ = 'I';
                    break;

                case '\x9a': //Κ
                case '\xba': //κ
                    *destination++ = 'K';
                    break;

                case '\x9b': //Λ
                case '\xbb': //λ
                    *destination++ = 'L';
                    break;

                case '\x9c': //Μ
                case '\xbc': //μ
                    *destination++ = 'M';
                    break;

                case '\x9d': //Ν
                case '\xbd': //ν
                    *destination++ = 'N';
                    break;

                case '\x9e': //Ξ
                case '\xbe': //ξ
                    *destination++ = 'X';
                    break;

                case '\x9f': //Ο
                case '\xbf': //ο
                    *destination++ = 'O';
                    break;

                case '\xa0': //Π
                    *destination++ = 'P';
                    break;

                case '\xa1': //Ρ
                    *destination++ = 'R';
                    break;

                case '\xa3': //Σ
                    *destination++ = 'S';
                    break;

                case '\xa4': //Τ
                    *destination++ = 'T';
                    break;

                case '\xa5': //Υ
                    *destination++ = 'Y';
                    break;

                case '\xa6': //Φ
                    *destination++ = 'F';
                    break;

                case '\xa7': //Χ
                    if (destinationEnd <= destination + 4)
                    {
                        *destination = '\0';
                        return 1;
                    }
                    *destination++ = '<';
                    *destination++ = 'M';
                    *destination++ = 'M';
                    *destination++ = '>';
                    break;

                case '\xa8': //Ψ
                    *destination++ = 'Q';
                    break;

                case '\xa9': //Ω
                    *destination++ = 'W';
                    break;

                default:
                    if (!_writeUnicodeFFFD(&destination, destinationEnd))
                    {
                        *destination = '\0';
                        return 1;
                    }
                    break;
            }

            sourceEnd += countUtf8Bytes;
            source = sourceEnd;
            continue;
        }

        if (sourceEnd[0] == '\xcf')
        {
            switch (sourceEnd[1])
            {
                case '\x80': //π
                    *destination++ = 'P';
                    break;

                case '\x81': //ρ
                    *destination++ = 'R';
                    break;

                case '\x82': //ς
                case '\x83': //σ
                    *destination++ = 'S';
                    break;

                case '\x84': //τ
                    *destination++ = 'T';
                    break;

                case '\x85': //υ
                    *destination++ = 'Y';
                    break;

                case '\x86': //φ
                    *destination++ = 'F';
                    break;

                case '\x87': //χ
                    if (destinationEnd <= destination + 4)
                    {
                        *destination = '\0';
                        return 1;
                    }
                    *destination++ = '<';
                    *destination++ = 'M';
                    *destination++ = 'M';
                    *destination++ = '>';
                    break;

                case '\x88': //ψ
                    *destination++ = 'Q';
                    break;

                case '\x89': //ω
                    *destination++ = 'W';
                    break;

                default:
                    if (!_writeUnicodeFFFD(&destination, destinationEnd))
                    {
                        *destination = '\0';
                        return 1;
                    }
                    break;
            }

            sourceEnd += countUtf8Bytes;
            source = sourceEnd;
            continue;
        }

        if (!_writeUnicodeFFFD(&destination, destinationEnd))
        {
            *destination = '\0';
            return 1;
        }

        sourceEnd += countUtf8Bytes;
        source = sourceEnd;
    }

    *destination = '\0';
    return 0;
}

