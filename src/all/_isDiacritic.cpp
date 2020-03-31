#include "_countUtf8Bytes.h"
#include "_isDiacritic.h"
#include "_utf8ToUnicode.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
bool _isDiacritic(const char *bytes)
{
    //Combining diacritics are Unicode code points U+0300 - U+036F.
    if (_countUtf8Bytes(bytes) == 2)
    {
        unsigned char unicodeHi = 0xff & bytes[0];
        unsigned char unicodeLo = 0xff & bytes[1];
        _utf8ToUnicode(&unicodeHi, &unicodeLo);
        return (unicodeHi == 0x03) && (unicodeLo <= 0x6f);
    }

    return false;
}
}

