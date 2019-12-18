#pragma once

#include <Arduino.h>
#include <stddef.h>

/*
Name

  convertMorseFromArabic

Description

  Converts a String object or a pointer to a String object containing Arabic
  characters into a null-terminated string only containing characters defined
  by Morse code.

  See the following for more details about Arabic Morse code:
  Morse code for non-Latin alphabets - Wikipedia
  https://en.wikipedia.org/wiki/Morse_code_for_non-Latin_alphabets

Syntax

  convertMorseFromArabic(arabicMessage, buffer, bufferSize)

Parameters

  arabicMessage
  The message containing English and Arabic characters.
  Any characters between <>, like "<SOS>", will be sent as a single pattern.
  "SK" would be the abbreviation for "Silent Key".
  "<SK>" would be the prosign for "End of contact".
  Angle brackets can be nested ("<SOS>" is the same as "<S<OS>>").
  Any unrecognized characters in the string converted to the Unicode
  replacement character (U+FFFD).

    The message can contain the following characters:
    Digits : 0123456789
    Symbols: "&'()+,-./:=?@
    Letters: AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz
             ÀàÄäÅåĄąÆæĆćĈĉÇçÐðÉéÈèĘęĜĝĤĥĴĵŃńÑñÓóÖöŚśŜŝŠšÞþÜüŬŭŹźŻż
             ﺍ ﺏ ﺕ ﺙ ﺝ ﺡ ﺥ ﺩ ﺫ ﺭ ﺯ ﺱ ﺵ ﺹ ﺽ ﻁ ﻅ ﻉ ﻍ ﻑ ﻕ ﻙ ﻝ ﻡ ﻥ ﻩ ﻭ ﻱ ﺀ
    Special: <>
    Space  :  

    ===========================================================================
    WARNING : Do not use accent marks on any Arabic character.
              Arabic Morse code does not use characters with accent marks.
    ===========================================================================

  buffer
  A character array that will contain the converted characters from
  arabicMessage.

  bufferSize
  The maximum number of bytes that buffer can contain.

Returns

  returns -1 if one or more of the following is true
    arabicMessage is nullptr
    buffer is nullptr
    bufferSize is less than 1

  returns non-zero
    on failure

  returns 0
    on success

Example Code

  const size_t morseBufferSize = 100;
  char morseBuffer[morseBufferSize];

  void loop()
  {
    convertMorseFromArabic("ﻡﺮﺤﺑﺍ", morseBuffer, morseBufferSize);
  }

Notes and Warnings

  Do not use accent marks on any Arabic character.
*/

int convertMorseFromArabic(const String &arabicMessage,
                           char buffer[],
                           size_t bufferSize);

int convertMorseFromArabic(const String *arabicMessage,
                           char buffer[],
                           size_t bufferSize);

