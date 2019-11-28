#include "_skipDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



bool _skipDiacritic(const char **bytes)
{
    if ((((*bytes)[0]) & 0xff) == 0xcc)
    {
        if ((0x80 <= ((*bytes)[1] & 0xff)) && (((*bytes)[1] & 0xff) <= 0xbf))
        {
            (*bytes) += 2;
            return true;
        }
    }

    if ((((*bytes)[0]) & 0xff) == 0xcd)
    {
        if ((0x80 <= ((*bytes)[1] & 0xff)) && (((*bytes)[1] & 0xff) <= 0xaf))
        {
            (*bytes) += 2;
            return true;
        }
    }

    return false;
}

