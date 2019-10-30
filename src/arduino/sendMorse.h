#pragma once

#include "../all/sendMorse.h"
#include <Arduino.h>

/*
Name

  sendMorse

Description

  Sends a null-terminated string, a String object, or a pointer to a String
  object as Morse code.

Syntax

  sendMorse(message, delayFunction, dotFunction, dashFunction)

Parameters

  message
  The message to send as Morse code
  Any unrecognized characters in the string will be considered as a space.
  Any characters between <>, like "<SOS>", will be sent as a single pattern.
  "SK" would be the abbreviation for "Silent Key".
  "<SK>" would be the prosign for "End of contact".

  delayFunction
  A function that delays for a short time.
  The delayFunction will be used to space the dots and dashes between letters and words.
  This function should be allowed to be called without arguments.

  dotFunction
  A function that creates a dot (a blinking LED, a beeping speaker, etc.).
  This function should be allowed to be called without arguments.

  dashFunction
  A function that creates a dash (a blinking LED, a beeping speaker, etc.).
  This function should be allowed to be called without arguments.

Returns

  Nothing

Example Code

  void setup()
  {
      pinMode(LED_BUILTIN, OUTPUT);
  }

  void loop()
  {
      sendMorse("<SOS>", ledDelay, ledDot, ledDash);
      
      String message = "<SOS>";
      sendMorse(message, ledDelay, ledDot, ledDash);

      String *ptr = &message;
      sendMorse(ptr, ledDelay, ledDot, ledDash);
  }

  void ledDelay()
  {
      delay(200);
  }

  void ledDot()
  {
      digitalWrite(LED_BUILTIN, HIGH);
      ledDelay();
      digitalWrite(LED_BUILTIN, LOW);
  }

  void ledDash()
  {
      digitalWrite(LED_BUILTIN, HIGH);
      ledDelay();
      ledDelay();
      ledDelay();
      digitalWrite(LED_BUILTIN, LOW);
  }

Notes and Warnings

  The duration of dotFunction should be the same as the duration of delayFunction.
  The duration of dashFunction should be three times the duration of delayFunction.
*/

void sendMorse(const String &message, void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)());

void sendMorse(const String *message, void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)());
