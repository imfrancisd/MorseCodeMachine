#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



//unsigned int _enToMorseElements(char)
//unsigned int _enToMorseElements(char **)
//
//16-bit return value format:
//aaaaaaa0bbbbbbb0
//aaaaaaa0 = number of morse elements as a series of 1
//bbbbbbb0 = morse elements as a series of 0 1, 0 is dit, 1 is dah
//
//Example:
//char '1' is morse dit dah dah dah dah
//aaaaaaa0 = 11111000 (5 morse elements, 5 1 starting from msb)
//bbbbbbb0 = 01111000 (dit dah dah dah dah)
//1111100001111000



//Returns Morse elements for ascii character from char.
unsigned int _enToMorseElements(char c);

//Returns Morse elements for utf8 character from **bytes.
unsigned int _enToMorseElements(const char **bytes);

