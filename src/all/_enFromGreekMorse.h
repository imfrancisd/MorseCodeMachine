#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



//Translate Greek Morse code to English Morse code.
//English equivalents of Greek characters are defined by Greek Morse code.
//Returns 0 on sucess.
//    *greek is incremented.
//    *english is incremented and contents modified.
//Returns 1 if *english does not have enough space. Nothing is modified.
//Returns 2 if no Greek character found. Nothing is modified.
int _enFromGreekMorse(const char **greek, char **english, const char *englishEnd);

