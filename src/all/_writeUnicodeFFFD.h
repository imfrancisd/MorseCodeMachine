#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



//Write U+FFFD in *dest using UTF-8 encoding and update *dest.
//On successful write, *dest < destEnd.
//Returns true on success.
//Returns false if there is not enough space in dest.
bool _writeUnicodeFFFD(char **dest, const char *destEnd);

