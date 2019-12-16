#include "_countUtf8Bytes.h"
#include "_enFromArabicMorse.h"
#include "_isDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
int _enFromArabicMorse(const char **arabic, char **english, const char *englishEnd)
{
    //Check if there is space to write in *english.
    if (englishEnd <= (*english) + 1)
    {
        goto ErrorNoSpace;
    }

    //Check if *arabic is U+FE80 (HAMZA ISOLATED FORM).

    if (_countUtf8Bytes(*arabic) == 3)
    {
        if (((*arabic)[0] != '\xef') ||
            ((*arabic)[1] != '\xba') ||
            ((*arabic)[2] != '\x80') ||
            (_isDiacritic((*arabic) + 3)))
        {
            goto ErrorNoMatch;
        }

        //ﺀ (HAMZA ISOLATED FORM) -> E
        *(*english)++ = '\x45';
        goto Success3;
    }

    //Check if *arabic is 2 byte UTF-8 character without diacritics following it.
    if ((_countUtf8Bytes(*arabic) != 2) || _isDiacritic((*arabic) + 2))
    {
        goto ErrorNoMatch;
    }

    //Convert 2 byte UTF-8 character to Unicode code point.
    unsigned char unicode[2];
    unicode[0] = 0x3f & (*arabic)[0];
    unicode[1] = 0x3f & (*arabic)[1];
    unicode[1] = unicode[1] | (0xc0 & (unicode[0] << 6));
    unicode[0] = unicode[0] >> 2;

    //Arabic characters are Unicode code points U+0627 - U+064A.
    if (unicode[0] != 0x06)
    {
        goto ErrorNoMatch;
    }

    switch (unicode[1])
    {
        case 0x27:
            //ا (ALEF) -> A
            *(*english)++ = '\x41';
            goto Success2;

        case 0x28:
            //ب (BEH) -> B
            *(*english)++ = '\x42';
            goto Success2;

        case 0x2a:
            //ت (TEH) -> T
            *(*english)++ = '\x54';
            goto Success2;

        case 0x2b:
            //ث (THEH) -> C
            *(*english)++ = '\x43';
            goto Success2;

        case 0x2c:
            //ج (JEEM) -> J
            *(*english)++ = '\x4a';
            goto Success2;

        case 0x2d:
            //ح (HAH) -> H
            *(*english)++ = '\x48';
            goto Success2;

        case 0x2e:
            //خ (KHAH) -> O
            *(*english)++ = '\x4f';
            goto Success2;

        case 0x2f:
            //د (DAL) -> D
            *(*english)++ = '\x44';
            goto Success2;

        case 0x30:
            //ذ (THAL) -> Z
            *(*english)++ = '\x5a';
            goto Success2;

        case 0x31:
            //ر (REH) -> R
            *(*english)++ = '\x52';
            goto Success2;

        case 0x32:
            //ز (ZAIN) -> <OE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x4f';
            *(*english)++ = '\x45';
            *(*english)++ = '\x3e';
            goto Success2;

        case 0x33:
            //س (SEEN) -> S
            *(*english)++ = '\x53';
            goto Success2;

        case 0x34:
            //ش (SHEEN) -> <MM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x4d';
            *(*english)++ = '\x4d';
            *(*english)++ = '\x3e';
            goto Success2;

        case 0x35:
            //ص (SAD) -> X
            *(*english)++ = '\x58';
            goto Success2;

        case 0x36:
            //ض (DAD) -> V
            *(*english)++ = '\x56';
            goto Success2;

        case 0x37:
            //ط (TAH) -> U
            *(*english)++ = '\x55';
            goto Success2;

        case 0x38:
            //ظ (ZAH) -> Y
            *(*english)++ = '\x59';
            goto Success2;

        case 0x39:
            //ع (AIN) -> <AA>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x41';
            *(*english)++ = '\x41';
            *(*english)++ = '\x3e';
            goto Success2;

        case 0x3a:
            //غ (GHAIN) -> G
            *(*english)++ = '\x47';
            goto Success2;

        case 0x41:
            //ف (FEH) -> F
            *(*english)++ = '\x46';
            goto Success2;

        case 0x42:
            //ق (QAF) -> Q
            *(*english)++ = '\x51';
            goto Success2;

        case 0x43:
            //ك (KAF) -> K
            *(*english)++ = '\x4b';
            goto Success2;

        case 0x44:
            //ل (LAM) -> L
            *(*english)++ = '\x4c';
            goto Success2;

        case 0x45:
            //م (MEEM) -> M
            *(*english)++ = '\x4d';
            goto Success2;

        case 0x46:
            //ن (NOON) -> N
            *(*english)++ = '\x4e';
            goto Success2;

        case 0x47:
            //ه (HEH) -> <FE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x46';
            *(*english)++ = '\x45';
            *(*english)++ = '\x3e';
            goto Success2;

        case 0x48:
            //و (WAW) -> W
            *(*english)++ = '\x57';
            goto Success2;

        case 0x4a:
            //ي (YEH) -> I
            *(*english)++ = '\x49';
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

