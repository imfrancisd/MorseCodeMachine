#pragma once

#ifdef ARDUINO

#include <Arduino.h>
#include <stddef.h>

#else

#include <stddef.h>
#include <string>

typedef std::string String;

#endif

/*
Name

  convertMorseFromPersian

Description

  Converts a String object or a pointer to a String object containing English
  and Persian characters into a null-terminated string containing only English
  characters defined by Morse code.

  See the following for more details about Persian Morse code:
  Morse code for non-Latin alphabets - Wikipedia
  https://en.wikipedia.org/wiki/Morse_code_for_non-Latin_alphabets

Syntax

  convertMorseFromPersian(persianMessage, englishBuffer, englishBufferSize)

Parameters

  persianMessage
  The message containing English and Persian characters.
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
             ا ب پ ت ث ج چ ح خ د ذ ر ز ژ س ش ص ض ط ظ ع غ ف ق ک گ ل م ن و ه ی
    Special: <>
    Space  :  

    ===========================================================================
    WARNING : Do not use accent marks on any Persian character.
              Persian Morse code does not use characters with accent marks.
    ===========================================================================

  englishBuffer
  A character array that will contain the converted characters from
  persianMessage.

  englishBufferSize
  The maximum number of bytes that englishBuffer can contain.

Returns

  returns -1 if one or more of the following is true
    persianMessage is nullptr
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
    convertMorseFromPersian("سلام", morseBuffer, morseBufferSize);
  }

Notes and Warnings

  Do not use accent marks on any Persian character.
*/

int convertMorseFromPersian(const String &persianMessage,
                            char englishBuffer[],
                            size_t englishBufferSize);

int convertMorseFromPersian(const String *persianMessage,
                            char englishBuffer[],
                            size_t englishBufferSize);

