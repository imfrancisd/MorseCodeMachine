#include "sendMorse.h"
#include "../all/sendMorse.h"
#include <Arduino.h>

void sendMorse(const String &message, void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    sendMorse(message.c_str(), delayFunction, dotFunction, dashFunction);
}

void sendMorse(const String *message, void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    if (message)
    {
        sendMorse(message->c_str(), delayFunction, dotFunction, dashFunction);
    }
}

void sendMorse(const String &message, void (*delayFunction)(void *context), void (*dotFunction)(void *context), void (*dashFunction)(void *context), void *context)
{
    sendMorse(message.c_str(), delayFunction, dotFunction, dashFunction, context);
}

void sendMorse(const String *message, void (*delayFunction)(void *context), void (*dotFunction)(void *context), void (*dashFunction)(void *context), void *context)
{
    if (message)
    {
        sendMorse(message->c_str(), delayFunction, dotFunction, dashFunction, context);
    }
}

