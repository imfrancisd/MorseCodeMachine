#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



//Skip combining diacritic character (U+0300 - U+036F).
bool _skipDiacritic(const char **bytes);

