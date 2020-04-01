#include "_writeUnicodeFFFD.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
bool _writeUnicodeFFFD(unsigned char **dest, const unsigned char *destEnd)
{
    if (destEnd <= (*dest) + 3)
    {
        return false;
    }

    *(*dest)++ = 0xef;
    *(*dest)++ = 0xbf;
    *(*dest)++ = 0xbd;
    return true;
}
}

