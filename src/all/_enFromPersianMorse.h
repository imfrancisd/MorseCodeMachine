#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
//Translate Persian Morse code to English Morse code.
//English equivalents of Persian characters are defined by Persian Morse code.
//Returns 0 on success.
//    *persian is incremented.
//    *english is incremented and contents modified.
//Returns 1 if *english does not have enough space. Nothing is modified.
//Returns 2 if no Persian character found. Nothing is modified.
int _enFromPersianMorse(const unsigned char **persian, unsigned char **english, const unsigned char *englishEnd);
}

