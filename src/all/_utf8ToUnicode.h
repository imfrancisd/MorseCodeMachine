#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
//Convert 2 byte UTF8 pattern to Unicode code point.
//The input will be overwritten by the output.
//No check is done if the UTF8 input is valid.
void _utf8ToUnicode(unsigned char *utf8Hi, unsigned char *utf8Lo);
}

