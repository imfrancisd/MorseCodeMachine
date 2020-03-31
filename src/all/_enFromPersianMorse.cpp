#include "_countUtf8Bytes.h"
#include "_enFromPersianMorse.h"
#include "_isDiacritic.h"
#include "_utf8ToUnicode.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
int _enFromPersianMorse(const char **persian, char **english, const char *englishEnd)
{
    unsigned char unicodeHi;
    unsigned char unicodeLo;

    //Check if there is space to write in *english.
    if (englishEnd <= (*english) + 1)
    {
        goto ErrorNoSpace;
    }

    //Check if *persian is 2 byte UTF-8 character without diacritics following it.
    if ((_countUtf8Bytes(*persian) != 2) || _isDiacritic((*persian) + 2))
    {
        goto ErrorNoMatch;
    }

    //Convert 2 byte UTF-8 character to Unicode code point.
    unicodeHi = 0xff & (*persian)[0];
    unicodeLo = 0xff & (*persian)[1];
    _utf8ToUnicode(&unicodeHi, &unicodeLo);

    //Persian characters are Unicode code points U+0600 - U+06FF.
    if (unicodeHi != 0x06)
    {
        goto ErrorNoMatch;
    }

    switch (unicodeLo)
    {
        case 0x27:
            //ا (ALEF) -> A
            *(*english)++ = '\x41';
            goto Success;

        case 0x28:
            //ب (BEH) -> B
            *(*english)++ = '\x42';
            goto Success;

        case 0x2a:
            //ت (TEH) -> T
            *(*english)++ = '\x54';
            goto Success;

        case 0x2b:
            //ث (THEH) -> C
            *(*english)++ = '\x43';
            goto Success;

        case 0x2c:
            //ج (JEEM) -> J
            *(*english)++ = '\x4a';
            goto Success;

        case 0x2d:
            //ح (HAH) -> H
            *(*english)++ = '\x48';
            goto Success;

        case 0x2e:
            //خ (KHAH) -> X
            *(*english)++ = '\x58';
            goto Success;

        case 0x2f:
            //د (DAL) -> D
            *(*english)++ = '\x44';
            goto Success;

        case 0x30:
            //ذ (THAL) -> V
            *(*english)++ = '\x56';
            goto Success;

        case 0x31:
            //ر (REH) -> R
            *(*english)++ = '\x52';
            goto Success;

        case 0x32:
            //ز (ZAIN) -> Z
            *(*english)++ = '\x5a';
            goto Success;

        case 0x33:
            //س (SEEN) -> S
            *(*english)++ = '\x53';
            goto Success;

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
            goto Success;

        case 0x35:
            //ص (SAD) -> <AA>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x41';
            *(*english)++ = '\x41';
            *(*english)++ = '\x3e';
            goto Success;

        case 0x36:
            //ض (DAD) -> <FE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x46';
            *(*english)++ = '\x45';
            *(*english)++ = '\x3e';
            goto Success;

        case 0x37:
            //ط (TAH) -> U
            *(*english)++ = '\x55';
            goto Success;

        case 0x38:
            //ظ (ZAH) -> Y
            *(*english)++ = '\x59';
            goto Success;

        case 0x39:
            //ع (AIN) -> O
            *(*english)++ = '\x4f';
            goto Success;

        case 0x3a:
            //غ (GHAIN) -> <IM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x49';
            *(*english)++ = '\x4d';
            *(*english)++ = '\x3e';
            goto Success;

        case 0x41:
            //ف (FEH) -> F
            *(*english)++ = '\x46';
            goto Success;

        case 0x42:
            //ق (QAF) -> <OS>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x4f';
            *(*english)++ = '\x53';
            *(*english)++ = '\x3e';
            goto Success;

        case 0x44:
            //ل (LAM) -> L
            *(*english)++ = '\x4c';
            goto Success;

        case 0x45:
            //م (MEEM) -> M
            *(*english)++ = '\x4d';
            goto Success;

        case 0x46:
            //ن (NOON) -> N
            *(*english)++ = '\x4e';
            goto Success;

        case 0x47:
            //ه (HEH) -> E
            *(*english)++ = '\x45';
            goto Success;

        case 0x48:
            //و (WAW) -> W
            *(*english)++ = '\x57';
            goto Success;

        case 0x7e:
            //پ (PEH) -> P
            *(*english)++ = '\x50';
            goto Success;

        case 0x86:
            //چ (TCHEH) -> <OE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x4f';
            *(*english)++ = '\x45';
            *(*english)++ = '\x3e';
            goto Success;

        case 0x98:
            //ژ (JEH) -> G
            *(*english)++ = '\x47';
            goto Success;

        case 0xa9:
            //ک (KEHEH) -> K
            *(*english)++ = '\x4b';
            goto Success;

        case 0xaf:
            //گ (GAF) -> Q
            *(*english)++ = '\x51';
            goto Success;

        case 0xcc:
            //ی (YEH) -> I
            *(*english)++ = '\x49';
            goto Success;

        default:
            goto ErrorNoMatch;
    }

Success:
    (*persian)+=2;
    return 0;

ErrorNoSpace:
    return 1;

ErrorNoMatch:
    return 2;
}
}

