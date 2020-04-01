#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
//Translate Russian Morse code to English Morse code.
//English equivalents of Russian characters are defined by Russian Morse code.
//Returns 0 on sucess.
//    *russian is incremented.
//    *english is incremented and contents modified.
//Returns 1 if *english does not have enough space. Nothing is modified.
//Returns 2 if no Russian character found. Nothing is modified.
int _enFromRussianMorse(const unsigned char **russian, unsigned char **english, const unsigned char *englishEnd);
}

