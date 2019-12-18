#pragma once

#include <Arduino.h>
#include <stddef.h>

/*
Name

  convertMorseFromRussian

Description

  Converts a String object or a pointer to a String object containing Russian
  characters into a null-terminated string only containing characters defined
  by Morse code.

  See the following for more details about Russian Morse code:
  Russian Morse Code - Wikipedia
  https://en.wikipedia.org/wiki/Russian_Morse_code

Syntax

  convertMorseFromRussian(russianMessage, buffer, bufferSize)

Parameters

  russianMessage
  The message containing Russian characters.
  Any characters between <>, like "<SOS>", will be sent as a single pattern.
  "SK" would be the abbreviation for "Silent Key".
  "<SK>" would be the prosign for "End of contact".
  Angle brackets can be nested ("<SOS>" is the same as "<S<OS>>").
  Any unrecognized characters in the string converted to the Unicode
  replacement character (U+FFFD).

    The message can contain the following characters:
    Digits : 0123456789
    Symbols: !"&'()+,-./:;=?@
    Letters: AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz
             ÀàÄäÅåĄąÆæĆćĈĉÇçÐðÉéÈèĘęĜĝĤĥĴĵŃńÑñÓóÖöŚśŜŝŠšÞþÜüŬŭŹźŻż
             АаБбВвГгДдЕеЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя
    Special: <>
    Space  :  

    ===========================================================================
    WARNING : Do not use accent marks on any Russian character.
              Russian Morse code does not use characters with accent marks.
    ===========================================================================

  buffer
  A character array that will contain the converted characters from
  russianMessage.

  bufferSize
  The maximum number of bytes that buffer can contain.

Returns

  returns -1 if one or more of the following is true
    russianMessage is nullptr
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
    convertMorseFromRussian("Здравствуй", morseBuffer, morseBufferSize);
  }

Notes and Warnings

  Do not use accent marks on any Russian character.
*/

int convertMorseFromRussian(const String &russianMessage,
                            char buffer[],
                            size_t bufferSize);

int convertMorseFromRussian(const String *russianMessage,
                            char buffer[],
                            size_t bufferSize);

