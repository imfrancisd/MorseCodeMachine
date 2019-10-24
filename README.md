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
