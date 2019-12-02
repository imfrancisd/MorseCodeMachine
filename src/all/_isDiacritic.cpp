#include "_isDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



bool _isDiacritic(const char *bytes)
{
    if ((bytes[0] == '\xcc') && (0x80 <= (bytes[1] & 0xff)) && ((bytes[1] & 0xff) <= 0xbf))
    {
        return true;
    }

    if ((bytes[0] == '\xcd') && (0x80 <= (bytes[1] & 0xff)) && ((bytes[1] & 0xff) <= 0xaf))
    {
        return true;
    }

    return false;
}

