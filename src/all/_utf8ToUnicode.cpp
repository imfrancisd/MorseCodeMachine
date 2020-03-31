#include "_utf8ToUnicode.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
void _utf8ToUnicode(unsigned char *utf8Hi, unsigned char *utf8Lo)
{
    *utf8Hi = 0x3f & *utf8Hi;
    *utf8Lo = 0x3f & *utf8Lo;
    *utf8Lo = *utf8Lo | (0xc0 & (*utf8Hi << 6));
    *utf8Hi = *utf8Hi >> 2;
}
}

