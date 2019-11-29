#include "_isDiacritic.h"
#include "_skipDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



bool _skipDiacritic(const char **bytes)
{
    if (_isDiacritic(*bytes))
    {
        (*bytes) += 2;
        return true;
    }

    return false;
}

