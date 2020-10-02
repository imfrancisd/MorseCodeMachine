#include "_countUtf8Bytes.h"
#include "_enFromRussianMorse.h"
#include "_isDiacritic.h"
#include "_utf8ToUnicode.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
int _enFromRussianMorse(const unsigned char **russian, unsigned char **english, const unsigned char *englishEnd)
{
    unsigned char unicodeHi;
    unsigned char unicodeLo;

    //Check if there is space to write in *english.
    if (englishEnd <= (*english) + 1)
    {
        goto ErrorNoSpace;
    }

    //Some symbols for Russian Morse code are different from symbols for English Morse code.
    if (_countUtf8Bytes(*russian) == 1)
    {
        //Check if *russian is 1 byte UTF-8 character without diacritics following it.
        if (_isDiacritic((*russian) + 1))
        {
            goto ErrorNoMatch;
        }

        unsigned char ascii = (*russian)[0];
        switch (ascii)
        {
            case 0x21:
                //! -> ,
                *(*english)++ = 0x2c;
                goto Success1;

            case 0x28:
                //( -> )
                *(*english)++ = 0x29;
                goto Success1;

            case 0x2c:
                //, -> .
                *(*english)++ = 0x2e;
                goto Success1;

            case 0x2d:
                //- -> =
                *(*english)++ = 0x3d;
                goto Success1;

            case 0x2e:
                //. -> <5E>
                if (englishEnd <= (*english) + 4)
                {
                    goto ErrorNoSpace;
                }
                *(*english)++ = 0x3c;
                *(*english)++ = 0x35;
                *(*english)++ = 0x45;
                *(*english)++ = 0x3e;
                goto Success1;

            case 0x3b:
                //; -> <CT>
                if (englishEnd <= (*english) + 4)
                {
                    goto ErrorNoSpace;
                }
                *(*english)++ = 0x3c;
                *(*english)++ = 0x43;
                *(*english)++ = 0x54;
                *(*english)++ = 0x3e;
                goto Success1;

            default:
                goto ErrorNoMatch;
        }
    }

    //Check if *russian is 2 byte UTF-8 character without diacritics following it.
    if ((_countUtf8Bytes(*russian) != 2) || _isDiacritic((*russian) + 2))
    {
        goto ErrorNoMatch;
    }

    //Convert 2 byte UTF-8 character to Unicode code point.
    unicodeHi = (*russian)[0];
    unicodeLo = (*russian)[1];
    _utf8ToUnicode(&unicodeHi, &unicodeLo);

    //Russian characters are Unicode code points U+0400 - U+04FF.
    if (unicodeHi != 0x04)
    {
        goto ErrorNoMatch;
    }

    //Convert uppercase (А-Я) to lowercase (а-я).
    //Uppercase (U+0410 - U+042f)
    //Lowercase (U+0430 - U+044f)
    if ((0x10 <= unicodeLo) && (unicodeLo <= 0x2f))
    {
        unicodeLo += 0x20;
    }

    switch (unicodeLo)
    {
        case 0x30:
            //а (A) -> A
            *(*english)++ = 0x41;
            goto Success2;

        case 0x31:
            //б (BE) -> B
            *(*english)++ = 0x42;
            goto Success2;

        case 0x32:
            //в (VE) -> W
            *(*english)++ = 0x57;
            goto Success2;

        case 0x33:
            //г (GHE) -> G
            *(*english)++ = 0x47;
            goto Success2;

        case 0x34:
            //д (DE) -> D
            *(*english)++ = 0x44;
            goto Success2;

        case 0x35:
            //е (IE) -> E
            *(*english)++ = 0x45;
            goto Success2;

        case 0x36:
            //ж (ZHE) -> V
            *(*english)++ = 0x56;
            goto Success2;

        case 0x37:
            //з (ZE) -> Z
            *(*english)++ = 0x5a;
            goto Success2;

        case 0x38:
            //и (I) -> I
            *(*english)++ = 0x49;
            goto Success2;

        case 0x39:
            //й (SHORT I) -> J
            *(*english)++ = 0x4a;
            goto Success2;

        case 0x3a:
            //к (KA) -> K
            *(*english)++ = 0x4b;
            goto Success2;

        case 0x3b:
            //л (EL) -> L
            *(*english)++ = 0x4c;
            goto Success2;

        case 0x3c:
            //м (EM) -> M
            *(*english)++ = 0x4d;
            goto Success2;

        case 0x3d:
            //н (EN) -> N
            *(*english)++ = 0x4e;
            goto Success2;

        case 0x3e:
            //о (O) -> O
            *(*english)++ = 0x4f;
            goto Success2;

        case 0x3f:
            //п (PE) -> P
            *(*english)++ = 0x50;
            goto Success2;

        case 0x40:
            //р (ER) -> R
            *(*english)++ = 0x52;
            goto Success2;

        case 0x41:
            //с (ES) -> S
            *(*english)++ = 0x53;
            goto Success2;

        case 0x42:
            //т (TE) -> T
            *(*english)++ = 0x54;
            goto Success2;

        case 0x43:
            //у (U) -> U
            *(*english)++ = 0x55;
            goto Success2;

        case 0x44:
            //ф (EF) -> F
            *(*english)++ = 0x46;
            goto Success2;

        case 0x45:
            //х (HA) -> H
            *(*english)++ = 0x48;
            goto Success2;

        case 0x46:
            //ц (TSE) -> C
            *(*english)++ = 0x43;
            goto Success2;

        case 0x47:
            //ч (CHE) -> <OE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x4f;
            *(*english)++ = 0x45;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x48:
            //ш (SHA) -> <MM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x49:
            //щ (SHCHA) -> Q
            *(*english)++ = 0x51;
            goto Success2;

        case 0x4a:
            //ъ (HARD SIGN) -> <GM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x47;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x4b:
            //ы (YERU) -> Y
            *(*english)++ = 0x59;
            goto Success2;

        case 0x4c:
            //ь (SOFT SIGN) -> X
            *(*english)++ = 0x58;
            goto Success2;

        case 0x4d:
            //э (E) -> <FE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x46;
            *(*english)++ = 0x45;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x4e:
            //ю (YU) -> <IM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x49;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x4f:
            //я (YA) -> <AA>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x41;
            *(*english)++ = 0x41;
            *(*english)++ = 0x3e;
            goto Success2;

        default:
            goto ErrorNoMatch;
    }

Success2:
    (*russian)++;
Success1:
    (*russian)++;
    return 0;

ErrorNoSpace:
    return 1;

ErrorNoMatch:
    return 2;
}
}

