#pragma once

/*
Name

  sendMorse

Description

  Sends a null-terminated string as Morse code.

Syntax

  sendMorse(message, delayFunction, dotFunction, dashFunction)
  sendMorse(message, delayFunction, dotFunction, dashFunction, context)

Parameters

  message
  The message to send as Morse code.
  Any unrecognized characters in the string will be considered as a space.
  Any characters between <>, like "<SOS>", will be sent as a single pattern.
  "SK" would be the abbreviation for "Silent Key".
  "<SK>" would be the prosign for "End of contact".

  delayFunction
  A function that delays for a short time.
  The delayFunction will be used to space the dots and dashes between letters and words.

    The delay function can have 0 or 1 parameter:
    void dly() {}
    void dly(void *context) {}

    The delay function can return a non-zero error code:
    int dly() {}
    int dly(void *context) {}

  dotFunction
  A function that creates a dot (a blinking LED, a beeping speaker, etc.).

    The dot function can have 0 or 1 parameter:
    void dit() {}
    void dit(void *context) {}

    The dot function can return a non-zero error code:
    int dit() {}
    int dit(void *context) {}

  dashFunction
  A function that creates a dash (a blinking LED, a beeping speaker, etc.).

    The dash function can have 0 or 1 parameter:
    void dah() {}
    void dah(void *context) {}

    The dash function can return a non-zero error code:
    int dah() {}
    int dah(void *context) {}

  context
  A pointer to pass the delayFunction, dotFunction, and dashFunction.

    This gives your delayFunction, dotFunction, and dashFunction state
    without having to use global variables.

Returns

  void sendMorse(...
    returns nothing

  int sendMorse(...
    returns -1
      message is null
      delayFunction is null
      dotFunction is null
      dashFunction is null
    returns non-zero
      delayFunction returns non-zero
      dotFunction returns non-zero
      dashFunction returns non-zero
    returns 0
      on success

Example Code

  void setup()
  {
      pinMode(LED_BUILTIN, OUTPUT);
  }

  void loop()
  {
      sendMorse("Send <SOS> not SOS", ledDelay, ledDot, ledDash);
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

  The duration of dashFunction should be 3 times the duration of delayFunction.

  The sendMorse function does nothing if message, delayFunction, dotFunction,
  or dashFunction is null.

  The delayFunction, dotFunction, and dashFunction must:
    all have the same number of parameters
    all return nothing or all return an integer.
*/

void sendMorse(const char message[], void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)());
void sendMorse(const char message[], void (*delayFunction)(void *context), void (*dotFunction)(void *context), void (*dashFunction)(void *context), void *context);

int sendMorse(const char message[], int (*delayFunction)(), int (*dotFunction)(), int (*dashFunction)());
int sendMorse(const char message[], int (*delayFunction)(void *context), int (*dotFunction)(void *context), int (*dashFunction)(void *context), void *context);

