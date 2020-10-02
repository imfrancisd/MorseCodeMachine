#pragma once

/*
Name

  convertMorseFromArabic

Description

  Converts a null-terminated string containing English and Arabic characters
  into a null-terminated string containing only English characters defined by
  Morse code.

  See the following for more details about Arabic Morse code:
  Morse code for non-Latin alphabets - Wikipedia
  https://en.wikipedia.org/wiki/Morse_code_for_non-Latin_alphabets

Syntax

  convertMorseFromArabic(arabicMessage, englishBuffer, englishBufferSize)

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
             ÀàÄäÅåĄąÆæĆćĈĉÇçĐđÐðÉéÈèĘęĜĝĤĥĴĵŁłŃńÑñÓóÖöØøŚśŜŝŠšÞþÜüŬŭŹźŻż
             ﺍ ﺏ ﺕ ﺙ ﺝ ﺡ ﺥ ﺩ ﺫ ﺭ ﺯ ﺱ ﺵ ﺹ ﺽ ﻁ ﻅ ﻉ ﻍ ﻑ ﻕ ﻙ ﻝ ﻡ ﻥ ﻩ ﻭ ﻱ ﺀ
    Special: <>
    Space  :  

    ===========================================================================
    WARNING : Do not use accent marks on any Arabic character.
              Arabic Morse code does not use characters with accent marks.
    ===========================================================================

  englishBuffer
  A character array that will contain the converted characters from
  arabicMessage.

  englishBufferSize
  The maximum number of bytes that englishBuffer can contain.

Returns

  returns -1 if one or more of the following is true
    arabicMessage is nullptr
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
    convertMorseFromArabic("ﻡﺮﺤﺑﺍ", morseBuffer, morseBufferSize);
  }

Notes and Warnings

  Do not use accent marks on any Arabic character.
*/

#include <stddef.h>

#ifdef __cplusplus
extern "C"
#endif
int convertMorseFromArabic(const char arabicMessage[],
                           char englishBuffer[],
                           size_t englishBufferSize);

