#include "_isDiacritic.h"
#include "_skipDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
bool _skipDiacritic(const unsigned char **bytes)
{
    if (_isDiacritic(*bytes))
    {
        (*bytes) += 2;
        return true;
    }

    return false;
}
}

