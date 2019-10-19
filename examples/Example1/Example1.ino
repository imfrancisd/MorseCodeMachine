#include "MorseCodeMachine.h"

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    sendMorse("CQ CQ CQ DE ARDUINO K", ledDelay, ledDot, ledDash);
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
