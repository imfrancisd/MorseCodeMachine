#include "_writeUnicodeFFFD.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
bool _writeUnicodeFFFD(char **dest, const char *destEnd)
{
    if (destEnd <= (*dest) + 3)
    {
        return false;
    }

    *(*dest)++ = '\xef';
    *(*dest)++ = '\xbf';
    *(*dest)++ = '\xbd';
    return true;
}
}

