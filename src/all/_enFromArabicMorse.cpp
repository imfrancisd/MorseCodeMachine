#include "_countUtf8Bytes.h"
#include "_enFromArabicMorse.h"
#include "_isDiacritic.h"
#include "_utf8ToUnicode.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
int _enFromArabicMorse(const unsigned char **arabic, unsigned char **english, const unsigned char *englishEnd)
{
    unsigned char unicodeHi;
    unsigned char unicodeLo;

    //Check if there is space to write in *english.
    if (englishEnd <= (*english) + 1)
    {
        goto ErrorNoSpace;
    }

    //Check if *arabic is U+FE80 (HAMZA ISOLATED FORM).

    if (_countUtf8Bytes(*arabic) == 3)
    {
        if (((*arabic)[0] != 0xef) ||
            ((*arabic)[1] != 0xba) ||
            ((*arabic)[2] != 0x80) ||
            (_isDiacritic((*arabic) + 3)))
        {
            goto ErrorNoMatch;
        }

        //ﺀ (HAMZA ISOLATED FORM) -> E
        *(*english)++ = 0x45;
        goto Success3;
    }

    //Check if *arabic is 2 byte UTF-8 character without diacritics following it.
    if ((_countUtf8Bytes(*arabic) != 2) || _isDiacritic((*arabic) + 2))
    {
        goto ErrorNoMatch;
    }

    //Convert 2 byte UTF-8 character to Unicode code point.
    unicodeHi = (*arabic)[0];
    unicodeLo = (*arabic)[1];
    _utf8ToUnicode(&unicodeHi, &unicodeLo);

    //Arabic characters are Unicode code points U+0627 - U+064A.
    if (unicodeHi != 0x06)
    {
        goto ErrorNoMatch;
    }

    switch (unicodeLo)
    {
        case 0x27:
            //ا (ALEF) -> A
            *(*english)++ = 0x41;
            goto Success2;

        case 0x28:
            //ب (BEH) -> B
            *(*english)++ = 0x42;
            goto Success2;

        case 0x2a:
            //ت (TEH) -> T
            *(*english)++ = 0x54;
            goto Success2;

        case 0x2b:
            //ث (THEH) -> C
            *(*english)++ = 0x43;
            goto Success2;

        case 0x2c:
            //ج (JEEM) -> J
            *(*english)++ = 0x4a;
            goto Success2;

        case 0x2d:
            //ح (HAH) -> H
            *(*english)++ = 0x48;
            goto Success2;

        case 0x2e:
            //خ (KHAH) -> O
            *(*english)++ = 0x4f;
            goto Success2;

        case 0x2f:
            //د (DAL) -> D
            *(*english)++ = 0x44;
            goto Success2;

        case 0x30:
            //ذ (THAL) -> Z
            *(*english)++ = 0x5a;
            goto Success2;

        case 0x31:
            //ر (REH) -> R
            *(*english)++ = 0x52;
            goto Success2;

        case 0x32:
            //ز (ZAIN) -> <OE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x4f;
            *(*english)++ = 0x45;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x33:
            //س (SEEN) -> S
            *(*english)++ = 0x53;
            goto Success2;

        case 0x34:
            //ش (SHEEN) -> <MM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x35:
            //ص (SAD) -> X
            *(*english)++ = 0x58;
            goto Success2;

        case 0x36:
            //ض (DAD) -> V
            *(*english)++ = 0x56;
            goto Success2;

        case 0x37:
            //ط (TAH) -> U
            *(*english)++ = 0x55;
            goto Success2;

        case 0x38:
            //ظ (ZAH) -> Y
            *(*english)++ = 0x59;
            goto Success2;

        case 0x39:
            //ع (AIN) -> <AA>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x41;
            *(*english)++ = 0x41;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x3a:
            //غ (GHAIN) -> G
            *(*english)++ = 0x47;
            goto Success2;

        case 0x41:
            //ف (FEH) -> F
            *(*english)++ = 0x46;
            goto Success2;

        case 0x42:
            //ق (QAF) -> Q
            *(*english)++ = 0x51;
            goto Success2;

        case 0x43:
            //ك (KAF) -> K
            *(*english)++ = 0x4b;
            goto Success2;

        case 0x44:
            //ل (LAM) -> L
            *(*english)++ = 0x4c;
            goto Success2;

        case 0x45:
            //م (MEEM) -> M
            *(*english)++ = 0x4d;
            goto Success2;

        case 0x46:
            //ن (NOON) -> N
            *(*english)++ = 0x4e;
            goto Success2;

        case 0x47:
            //ه (HEH) -> <FE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x46;
            *(*english)++ = 0x45;
            *(*english)++ = 0x3e;
            goto Success2;

        case 0x48:
            //و (WAW) -> W
            *(*english)++ = 0x57;
            goto Success2;

        case 0x4a:
            //ي (YEH) -> I
            *(*english)++ = 0x49;
            goto Success2;

        default:
            goto ErrorNoMatch;
    }

Success3:
    (*arabic)++;
Success2:
    (*arabic)++;
    (*arabic)++;
    return 0;

ErrorNoSpace:
    return 1;

ErrorNoMatch:
    return 2;
}
}

