#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
//Write U+FFFD in *dest using UTF-8 encoding and update *dest.
//On successful write, *dest < destEnd.
//Returns true on success.
//Returns false if there is not enough space in dest.
bool _writeUnicodeFFFD(unsigned char **dest, const unsigned char *destEnd);
}

