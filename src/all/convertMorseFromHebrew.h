#pragma once

#include <stddef.h>

/*
Name

  convertMorseFromHebrew

Description

  Converts a null-terminated string containing English and Hebrew characters
  into a null-terminated string containing only English characters defined by
  Morse code.

  See the following for more details about Hebrew Morse code:
  Morse code for non-Latin alphabets - Wikipedia
  https://en.wikipedia.org/wiki/Morse_code_for_non-Latin_alphabets

Syntax

  convertMorseFromHebrew(hebrewMessage, englishBuffer, englishBufferSize)

Parameters

  hebrewMessage
  The message containing English and Hebrew characters.
  Any characters between <>, like "<SOS>", will be sent as a single pattern.
  "SK" would be the abbreviation for "Silent Key".
  "<SK>" would be the prosign for "End of contact".
  Angle brackets can be nested ("<SOS>" is the same as "<S<OS>>").
  Any unrecognized characters in the string converted to the Unicode
  replacement character (U+FFFD).

    The message can contain the following characters:
    Digits : 0123456789
    Symbols: "&'()+,-./:=?@
    Letters: AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzÉé
             א ב ג ד ה ו ז ח ט י ך כ ל ם מ ן נ ס ע ף פ ץ צ ק ר ש ת
    Special: <>
    Space  :  

    ===========================================================================
    WARNING : Do not use accent marks on any Hebrew character.
              Hebrew Morse code does not use characters with accent marks.
    ===========================================================================

  englishBuffer
  A character array that will contain the converted characters from
  hebrewMessage.

  englishBufferSize
  The maximum number of bytes that englishBuffer can contain.

Returns

  returns -1 if one or more of the following is true
    hebrewMessage is nullptr
    englishBuffer is nullptr
    englishBufferSize is less than 1

  returns non-zero
    on failure

  returns 0
    on success

Example Code

  const size_t morseBufferSize = 100;
  char morseBuffer[morseBufferSize];

  void loop()
  {
    convertMorseFromHebrew("שלום", morseBuffer, morseBufferSize);
  }

Notes and Warnings

  Do not use accent marks on any Hebrew character.
*/

int convertMorseFromHebrew(const char hebrewMessage[],
                           char englishBuffer[],
                           size_t englishBufferSize);

