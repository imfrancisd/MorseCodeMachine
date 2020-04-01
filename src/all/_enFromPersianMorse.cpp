#include "_countUtf8Bytes.h"
#include "_enFromPersianMorse.h"
#include "_isDiacritic.h"
#include "_utf8ToUnicode.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
int _enFromPersianMorse(const unsigned char **persian, unsigned char **english, const unsigned char *englishEnd)
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
    unicodeHi = (*persian)[0];
    unicodeLo = (*persian)[1];
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
            *(*english)++ = 0x41;
            goto Success;

        case 0x28:
            //ب (BEH) -> B
            *(*english)++ = 0x42;
            goto Success;

        case 0x2a:
            //ت (TEH) -> T
            *(*english)++ = 0x54;
            goto Success;

        case 0x2b:
            //ث (THEH) -> C
            *(*english)++ = 0x43;
            goto Success;

        case 0x2c:
            //ج (JEEM) -> J
            *(*english)++ = 0x4a;
            goto Success;

        case 0x2d:
            //ح (HAH) -> H
            *(*english)++ = 0x48;
            goto Success;

        case 0x2e:
            //خ (KHAH) -> X
            *(*english)++ = 0x58;
            goto Success;

        case 0x2f:
            //د (DAL) -> D
            *(*english)++ = 0x44;
            goto Success;

        case 0x30:
            //ذ (THAL) -> V
            *(*english)++ = 0x56;
            goto Success;

        case 0x31:
            //ر (REH) -> R
            *(*english)++ = 0x52;
            goto Success;

        case 0x32:
            //ز (ZAIN) -> Z
            *(*english)++ = 0x5a;
            goto Success;

        case 0x33:
            //س (SEEN) -> S
            *(*english)++ = 0x53;
            goto Success;

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
            goto Success;

        case 0x35:
            //ص (SAD) -> <AA>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x41;
            *(*english)++ = 0x41;
            *(*english)++ = 0x3e;
            goto Success;

        case 0x36:
            //ض (DAD) -> <FE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x46;
            *(*english)++ = 0x45;
            *(*english)++ = 0x3e;
            goto Success;

        case 0x37:
            //ط (TAH) -> U
            *(*english)++ = 0x55;
            goto Success;

        case 0x38:
            //ظ (ZAH) -> Y
            *(*english)++ = 0x59;
            goto Success;

        case 0x39:
            //ع (AIN) -> O
            *(*english)++ = 0x4f;
            goto Success;

        case 0x3a:
            //غ (GHAIN) -> <IM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x49;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x3e;
            goto Success;

        case 0x41:
            //ف (FEH) -> F
            *(*english)++ = 0x46;
            goto Success;

        case 0x42:
            //ق (QAF) -> <OS>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x4f;
            *(*english)++ = 0x53;
            *(*english)++ = 0x3e;
            goto Success;

        case 0x44:
            //ل (LAM) -> L
            *(*english)++ = 0x4c;
            goto Success;

        case 0x45:
            //م (MEEM) -> M
            *(*english)++ = 0x4d;
            goto Success;

        case 0x46:
            //ن (NOON) -> N
            *(*english)++ = 0x4e;
            goto Success;

        case 0x47:
            //ه (HEH) -> E
            *(*english)++ = 0x45;
            goto Success;

        case 0x48:
            //و (WAW) -> W
            *(*english)++ = 0x57;
            goto Success;

        case 0x7e:
            //پ (PEH) -> P
            *(*english)++ = 0x50;
            goto Success;

        case 0x86:
            //چ (TCHEH) -> <OE>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x4f;
            *(*english)++ = 0x45;
            *(*english)++ = 0x3e;
            goto Success;

        case 0x98:
            //ژ (JEH) -> G
            *(*english)++ = 0x47;
            goto Success;

        case 0xa9:
            //ک (KEHEH) -> K
            *(*english)++ = 0x4b;
            goto Success;

        case 0xaf:
            //گ (GAF) -> Q
            *(*english)++ = 0x51;
            goto Success;

        case 0xcc:
            //ی (YEH) -> I
            *(*english)++ = 0x49;
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

