#pragma once

#include <Arduino.h>
#include <stddef.h>

/*
Name

  convertMorseFromGreek

Description

  Converts a String object or a pointer to a String object containing English
  and Greek characters into a null-terminated string containing only English
  characters defined by Morse code.

  See the following for more details about Greek Morse code:
  Morse code for non-Latin alphabets - Wikipedia
  https://en.wikipedia.org/wiki/Morse_code_for_non-Latin_alphabets

Syntax

  convertMorseFromGreek(greekMessage, englishBuffer, englishBufferSize)

Parameters

  greekMessage
  The message containing English and Greek characters.
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
             ΑαΒβΓγΔδΕεΖζΗηΘθΙιΚκΛλΜμΝνΞξΟοΠπΡρΣςσΤτΥυΦφΧχΨψΩω
    Special: <>
    Space  :  

    ===========================================================================
    WARNING : Do not use accent marks on any Greek character.
              Greek Morse code does not use characters with accent marks.
    ===========================================================================

  englishBuffer
  A character array that will contain the converted characters from
  greekMessage.

  englishBufferSize
  The maximum number of bytes that englishBuffer can contain.

Returns

  returns -1 if one or more of the following is true
    greekMessage is nullptr
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
    convertMorseFromGreek("γεια", morseBuffer, morseBufferSize);
  }

Notes and Warnings

  Do not use accent marks on any Greek character.
*/

int convertMorseFromGreek(const String &greekMessage,
                          char englishBuffer[],
                          size_t englishBufferSize);

int convertMorseFromGreek(const String *greekMessage,
                          char englishBuffer[],
                          size_t englishBufferSize);

