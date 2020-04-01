#pragma once



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
//Returns Morse elements for utf8 character from **bytes.
//Moves pointer *bytes to next utf8 character.
//
//8-bit return value format:
//bbbbbbbb = morse elements as a series of 0 1, 0 is dit, 1 is dah
//           starts at msb
//           end of morse elements is followed by a 1
//
//Example:
//char 'Z' is morse dah dah dit dit
//bbbbbbbb = 11001000 (dah dah dit dit followed by a 1)
//
//For unrecognized characters:
//bbbbbbbb = 00000000
//
//For recognized characters that do not have Morse elements (' ', '<', '>'):
//bbbbbbbb = 10000000
unsigned char _enToMorseElements(const unsigned char **bytes);
}

