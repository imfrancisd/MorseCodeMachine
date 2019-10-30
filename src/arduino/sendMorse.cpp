#include "sendMorse.h"
#include "../all/sendMorse.h"
#include <Arduino.h>

void sendMorse(const String &message, void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    sendMorse(message.c_str(), delayFunction, dotFunction, dashFunction);
}

void sendMorse(const String *message, void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    sendMorse(message->c_str(), delayFunction, dotFunction, dashFunction);
}
