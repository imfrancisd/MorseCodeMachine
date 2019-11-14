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
  The delayFunction will be used to space the dots and dashes between
  characters and words.

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
  A pointer to pass to the delayFunction, dotFunction, and dashFunction.

    This gives your delayFunction, dotFunction, and dashFunction state
    without having to use global variables.

Returns

  void sendMorse(
    returns nothing

  int sendMorse(
    returns -1 if one or more of the following is true
      message is nullptr
      delayFunction is nullptr
      dotFunction is nullptr
      dashFunction is nullptr

    returns non-zero when
      delayFunction returns non-zero
      dotFunction returns non-zero
      dashFunction returns non-zero

      When any of the three functions returns a non-zero value, sendMorse will
      immediately stop and return that non-zero value.

    returns 0
      on success

Example Code

  //Functions that creates Morse code with a blinking LED.
  void ledDly();
  void ledDit();
  void ledDah();

  //Functions that creates Morse code with a spinning motor,
  //and returns a non-zero integer if there is an error.
  int motorDly();
  int motorDit();
  int motorDah();

  //Functions that creates Morse code with a beeping speaker,
  //and takes an integer to customize its speed (dot duration in ms).
  void speakerDly(void *);
  void speakerDit(void *);
  void speakerDah(void *);

  //Functions that creates Morse code with a super secret device,
  //and returns a non-zero integer if there is an error,
  //and takes a pointer to an object to customize its behavior.
  class SuperSecretDevicePreferences
  {
    public:
    SuperSecretDevicePreferences(int dotDuration, int red, int green, int blue);
    //more code
  };
  int superSecretDeviceDelay(void *);
  int superSecretDeviceDot(void *);
  int superSecretDeviceDash(void *);

  void loop()
  {
    const char message[] = "Send <SOS> not SOS";

    sendMorse(message, ledDly, ledDit, ledDah);

    int motorErrorCode = sendMorse(message, motorDly, motorDit, motorDah);
    if (motorErrorCode != 0)
    {
        //there was an error sending morse code
    }

    int dotDuration = 200;
    sendMorse(message, speakerDly, speakerDit, speakerDah, &dotDuration);

    SuperSecretDevicePreferences preferences(200, 255, 165, 0);
    int superSecretDeviceErrorCode = sendMorse(message,
                                               superSecretDeviceDelay,
                                               superSecretDeviceDot,
                                               superSecretDeviceDash,
                                               &preferences);
    if (superSecretDeviceErrorCode != 0)
    {
      //super secret device had error sending morse code
    }
  }

Notes and Warnings

  The duration of dotFunction should equal the duration of delayFunction.

  The duration of dashFunction should be 3 times the duration of delayFunction.

  The sendMorse function returns immediately if message, delayFunction,
  dotFunction, or dashFunction is nullptr.

  The delayFunction, dotFunction, and dashFunction must:
    all have the same number of parameters
    all return nothing or all return an integer.
*/

void sendMorse(const char message[],
               void (*delayFunction)(),
               void (*dotFunction)(),
               void (*dashFunction)());

int sendMorse(const char message[],
              int (*delayFunction)(),
              int (*dotFunction)(),
              int (*dashFunction)());

void sendMorse(const char message[],
               void (*delayFunction)(void *context),
               void (*dotFunction)(void *context),
               void (*dashFunction)(void *context),
               void *context);

int sendMorse(const char message[],
              int (*delayFunction)(void *context),
              int (*dotFunction)(void *context),
              int (*dashFunction)(void *context),
              void *context);

