#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
//Returns number of bytes in the UTF-8 character.
//Returns 0 for extended ascii or error in UTF-8 byte pattern.
//Returns 1, 2, 3, or 4 for ascii or valid UTF-8 byte pattern.
//Returns 1 for '\0'.
//Does not check for unassigned Unicode code points, only byte patterns.
unsigned char _countUtf8Bytes(const unsigned char *bytes);
}

