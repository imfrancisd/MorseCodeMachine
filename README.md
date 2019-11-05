# MorseCodeMachine

Get started with Arduino by learning Morse code.

Send Morse code using any device that you can blink, move, or beep with your Arduino.

From Arduino to anyone.
```
void loop() {
  sendMorse("CQ CQ CQ DE ARDUINO K", delayLed1, ditLed1, dahLed1);
}
```

From you to Arduino.
```
void loop() {
  sendMorse("ARDUINO DE YOU <KN>", delayLed2, ditLed2, dahLed2);
}
```

# Installing the library

Download the zip file of the latest release here:

https://github.com/imfrancisd/MorseCodeMachine/releases

Install the library by following the directions here:

https://www.arduino.cc/en/guide/libraries

# Library Functions

```
//Send Morse code with strings and  functions.
void sendMorse(const char message[], void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)());
void sendMorse(const String &message, void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)());
void sendMorse(const String *message, void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)());

//Send Morse code with strings and functions that return error codes.
int sendMorse(const char message[], int (*delayFunction)(), int (*dotFunction)(), int (*dashFunction)());
int sendMorse(const String &message, int (*delayFunction)(), int (*dotFunction)(), int (*dashFunction)());
int sendMorse(const String *message, int (*delayFunction)(), int (*dotFunction)(), int (*dashFunction)());

//Send Morse code with strings and functions that take a void * argument.
void sendMorse(const char message[], void (*delayFunction)(void *context), void (*dotFunction)(void *context), void (*dashFunction)(void *context), void *context);
void sendMorse(const String &message, void (*delayFunction)(void *context), void (*dotFunction)(void *context), void (*dashFunction)(void *context), void *context);
void sendMorse(const String *message, void (*delayFunction)(void *context), void (*dotFunction)(void *context), void (*dashFunction)(void *context), void *context);

//Send Morse code with strings and functions that take a void * argument and returns error codes.
int sendMorse(const char message[], int (*delayFunction)(void *context), int (*dotFunction)(void *context), int (*dashFunction)(void *context), void *context);
int sendMorse(const String &message, int (*delayFunction)(void *context), int (*dotFunction)(void *context), int (*dashFunction)(void *context), void *context);
int sendMorse(const String *message, int (*delayFunction)(void *context), int (*dotFunction)(void *context), int (*dashFunction)(void *context), void *context);
```

