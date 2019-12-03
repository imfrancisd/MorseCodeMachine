#include "_enFromGreekMorse.h"
#include "_isDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



bool _writeMM(char **english, const char *englishEnd)
{
    if (englishEnd <= (*english) + 4)
    {
        return false;
    }

    *(*english)++ = '<';
    *(*english)++ = 'M';
    *(*english)++ = 'M';
    *(*english)++ = '>';
    return true;
}

int _enFromGreekMorse(const char **greek, char **english, const char *englishEnd)
{
    if (englishEnd <= (*english) + 1)
    {
        //No space.
        return 1;
    }

    if ((*greek)[0] && (*greek)[1] && _isDiacritic((*greek) + 2))
    {
        //No match (Recognized Greek letters are two bytes without diacritics).
        return 2;
    }

    if ((*greek)[0] == '\xce')
    {
        switch ((*greek)[1])
        {
            case '\x91': //Α
            case '\xb1': //α
                *(*english)++ = 'A';
                break;

            case '\x92': //Β
            case '\xb2': //β
                *(*english)++ = 'B';
                break;

            case '\x93': //Γ
            case '\xb3': //γ
                *(*english)++ = 'G';
                break;

            case '\x94': //Δ
            case '\xb4': //δ
                *(*english)++ = 'D';
                break;

            case '\x95': //Ε
            case '\xb5': //ε
                *(*english)++ = 'E';
                break;

            case '\x96': //Ζ
            case '\xb6': //ζ
                *(*english)++ = 'Z';
                break;

            case '\x97': //Η
            case '\xb7': //η
                *(*english)++ = 'H';
                break;

            case '\x98': //Θ
            case '\xb8': //θ
                *(*english)++ = 'C';
                break;

            case '\x99': //Ι
            case '\xb9': //ι
                *(*english)++ = 'I';
                break;

            case '\x9a': //Κ
            case '\xba': //κ
                *(*english)++ = 'K';
                break;

            case '\x9b': //Λ
            case '\xbb': //λ
                *(*english)++ = 'L';
                break;

            case '\x9c': //Μ
            case '\xbc': //μ
                *(*english)++ = 'M';
                break;

            case '\x9d': //Ν
            case '\xbd': //ν
                *(*english)++ = 'N';
                break;

            case '\x9e': //Ξ
            case '\xbe': //ξ
                *(*english)++ = 'X';
                break;

            case '\x9f': //Ο
            case '\xbf': //ο
                *(*english)++ = 'O';
                break;

            case '\xa0': //Π
                *(*english)++ = 'P';
                break;

            case '\xa1': //Ρ
                *(*english)++ = 'R';
                break;

            case '\xa3': //Σ
                *(*english)++ = 'S';
                break;

            case '\xa4': //Τ
                *(*english)++ = 'T';
                break;

            case '\xa5': //Υ
                *(*english)++ = 'Y';
                break;

            case '\xa6': //Φ
                *(*english)++ = 'F';
                break;

            case '\xa7': //Χ
                if (!_writeMM(english, englishEnd))
                {
                    //No space.
                    return 1;
                }
                break;

            case '\xa8': //Ψ
                *(*english)++ = 'Q';
                break;

            case '\xa9': //Ω
                *(*english)++ = 'W';
                break;

            default:
                //No match.
                return 2;
        }

        //Success.
        (*greek) += 2;
        return 0;
    }

    if ((*greek)[0] == '\xcf')
    {
        switch ((*greek)[1])
        {
            case '\x80': //π
                *(*english)++ = 'P';
                break;

            case '\x81': //ρ
                *(*english)++ = 'R';
                break;

            case '\x82': //ς
            case '\x83': //σ
                *(*english)++ = 'S';
                break;

            case '\x84': //τ
                *(*english)++ = 'T';
                break;

            case '\x85': //υ
                *(*english)++ = 'Y';
                break;

            case '\x86': //φ
                *(*english)++ = 'F';
                break;

            case '\x87': //χ
                if (!_writeMM(english, englishEnd))
                {
                    //No space.
                    return 1;
                }
                break;

            case '\x88': //ψ
                *(*english)++ = 'Q';
                break;

            case '\x89': //ω
                *(*english)++ = 'W';
                break;

            default:
                //No match.
                return 2;
        }

        //Success.
        (*greek) += 2;
        return 0;
    }

    //No match.
    return 2;
}

