#pragma once

#include <stddef.h>

/*
Name

  convertMorseFromGreek

Description

  Converts a null-terminated string containing Greek characters into a
  null-terminated string only containing characters defined by Morse code.

  See the following for more details about Greek Morse code:
  Morse code for non-Latin alphabets - Wikipedia
  https://en.wikipedia.org/wiki/Morse_code_for_non-Latin_alphabets

Syntax

  convertMorseFromGreek(greekMessage, buffer, bufferSize)

Parameters

  greekMessage
  The message containing Greek characters.
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
             ΑαΒβΓγΔδΕεΖζΗηΘθΙιΚκΛλΜμΝνΞξΟοΠπΡρΣςσΤτΥυΦφΧχΨψΩω
    Special: <>
    Space  :  

    ===========================================================================
    WARNING : Do not use accent marks on any Greek character.
              Greek Morse code does not use characters with accent marks.
    ===========================================================================

  buffer
  A character array that will contain the converted characters from
  greekMessage.

  bufferSize
  The maximum number of bytes that buffer can contain.

Returns

  returns -1 if one or more of the following is true
    greekMessage is nullptr
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
    convertMorseFromGreek("γεια", morseBuffer, morseBufferSize);
  }

Notes and Warnings

  Do not use accent marks on any Greek character.
*/

int convertMorseFromGreek(const char greekMessage[],
                          char buffer[],
                          size_t bufferSize);

