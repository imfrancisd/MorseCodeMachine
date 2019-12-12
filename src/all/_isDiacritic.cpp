#include "_countUtf8Bytes.h"
#include "_isDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
bool _isDiacritic(const char *bytes)
{
    //Combining diacritics are Unicode code points U+0300 - U+036F.
    if (_countUtf8Bytes(bytes) == 2)
    {
        unsigned char unicode[2];
        unicode[0] = 0x3f & (bytes)[0];
        unicode[1] = 0x3f & (bytes)[1];
        unicode[1] = unicode[1] | (0xc0 & (unicode[0] << 6));
        unicode[0] = unicode[0] >> 2;
        return (unicode[0] == 0x03) && (unicode[1] <= 0x6f);
    }

    return false;
}
}

