# MorseCodeMachine

Get started with Arduino by learning Morse code.

Send Morse code using any device that you can blink, move, or beep with your Arduino.

```
#include <MorseCodeMachine.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  //From Arduino to anyone.
  sendMorse("CQ CQ CQ DE ARDUINO K", delayLed, ditLed, dahLed);

  //From you to Arduino.
  sendMorse("ARDUINO DE YOU <KN>", delayLed, ditLed, dahLed);
}

void delayLed() {
  delay(200);
}

void ditLed() {
  digitalWrite(LED_BUILTIN, HIGH);
  delayLed();
  digitalWrite(LED_BUILTIN, LOW);
}

void dahLed() {
  digitalWrite(LED_BUILTIN, HIGH);
  delayLed();
  delayLed();
  delayLed();
  digitalWrite(LED_BUILTIN, LOW);
}
```

# Multiple Language Support

See the examples to learn how to send Morse Code in another language, such as Greek.

# Installing the library

Download the zip file of the latest release here:

https://github.com/imfrancisd/MorseCodeMachine/releases

Install the library by following the directions here:

https://www.arduino.cc/en/guide/libraries

