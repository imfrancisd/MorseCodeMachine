#include "_countUtf8Bytes.h"
#include "_enFromHebrewMorse.h"
#include "_isDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
int _enFromHebrewMorse(const char **hebrew, char **english, const char *englishEnd)
{
    //Check if there is space to write in *english.
    if (englishEnd <= (*english) + 1)
    {
        goto ErrorNoSpace;
    }

    //Check if *hebrew is 2 byte UTF-8 character without diacritics following it.
    if ((_countUtf8Bytes(*hebrew) != 2) || _isDiacritic((*hebrew) + 2))
    {
        goto ErrorNoMatch;
    }

    //Convert 2 byte UTF-8 character to Unicode code point.
    unsigned char unicode[2];
    unicode[0] = 0x3f & (*hebrew)[0];
    unicode[1] = 0x3f & (*hebrew)[1];
    unicode[1] = unicode[1] | (0xc0 & (unicode[0] << 6));
    unicode[0] = unicode[0] >> 2;

    //Hebrew characters are Unicode code points U+05D0 - U+05EA.
    if (unicode[0] != 0x05)
    {
        goto ErrorNoMatch;
    }

    switch (unicode[1])
    {
        case 0xd0:
            //א (ALEF) -> A
            *(*english)++ = '\x41';
            goto Success;

        case 0xd1:
            //ב (BET) -> B
            *(*english)++ = '\x42';
            goto Success;

        case 0xd2:
            //ג (GIMEL) -> G
            *(*english)++ = '\x47';
            goto Success;

        case 0xd3:
            //ד (DALET) -> D
            *(*english)++ = '\x44';
            goto Success;

        case 0xd4:
            //ה (HE) -> O
            *(*english)++ = '\x4f';
            goto Success;

        case 0xd5:
            //ו (VAV) -> E
            *(*english)++ = '\x45';
            goto Success;

        case 0xd6:
            //ז (ZAYIN) -> Z
            *(*english)++ = '\x5a';
            goto Success;

        case 0xd7:
            //ח (HET) -> H
            *(*english)++ = '\x48';
            goto Success;

        case 0xd8:
            //ט (TET) -> U
            *(*english)++ = '\x55';
            goto Success;

        case 0xd9:
            //י (YOD) -> I
            *(*english)++ = '\x49';
            goto Success;

        case 0xda:
        case 0xdb:
            //ך (FINAL KAF) -> K
            //כ (KAF) -> K
            *(*english)++ = '\x4b';
            goto Success;

        case 0xdc:
            //ל (LAMED) -> L
            *(*english)++ = '\x4c';
            goto Success;

        case 0xdd:
        case 0xde:
            //ם (FINAL MEM) -> M
            //מ (MEM) -> M
            *(*english)++ = '\x4d';
            goto Success;

        case 0xdf:
        case 0xe0:
            //ן (FINAL NUN) -> N
            //נ (NUN) -> N
            *(*english)++ = '\x4e';
            goto Success;

        case 0xe1:
            //ס (SAMEKH) -> C
            *(*english)++ = '\x43';
            goto Success;

        case 0xe2:
            //ע (AYIN) -> J
            *(*english)++ = '\x4a';
            goto Success;

        case 0xe3:
        case 0xe4:
            //ף (FINAL PE) -> P
            //פ (PE) -> P
            *(*english)++ = '\x50';
            goto Success;

        case 0xe5:
        case 0xe6:
            //ץ (FINAL TSADI) -> W
            //צ (TSADI) -> W
            *(*english)++ = '\x57';
            goto Success;

        case 0xe7:
            //ק (QOF) -> Q
            *(*english)++ = '\x51';
            goto Success;

        case 0xe8:
            //ר (RESH) -> R
            *(*english)++ = '\x52';
            goto Success;

        case 0xe9:
            //ש (SHIN) -> S
            *(*english)++ = '\x53';
            goto Success;

        case 0xea:
            //ת (TAV) -> T
            *(*english)++ = '\x54';
            goto Success;

        default:
            goto ErrorNoMatch;
    }

Success:
    (*hebrew) += 2;
    return 0;

ErrorNoSpace:
    return 1;

ErrorNoMatch:
    return 2;
}
}

