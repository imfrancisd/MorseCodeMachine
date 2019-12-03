#include "_writeUnicodeFFFD.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



bool _writeUnicodeFFFD(char **dest, const char *destEnd)
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

