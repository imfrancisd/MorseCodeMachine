#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
//Translate Hebrew Morse code to English Morse code.
//English equivalents of Hebrew characters are defined by Hebrew Morse code.
//Returns 0 on sucess.
//    *hebrew is incremented.
//    *english is incremented and contents modified.
//Returns 1 if *english does not have enough space. Nothing is modified.
//Returns 2 if no Hebrew character found. Nothing is modified.
int _morseFromHebrew(const char **hebrew, char **english, const char *englishEnd);
}

