#include <MorseCodeMachine.h>

class LEDMorseCodeMachine
{
    public:
    LEDMorseCodeMachine(int outputPin, int dotDuration)
    {
        _outputPin = outputPin;
        _dotDuration = dotDuration;
    }
    int ledDelay()
    {
        delay(_dotDuration);
        return 0;
    }
    int ledDot()
    {
        digitalWrite(_outputPin, HIGH);
        ledDelay();
        digitalWrite(_outputPin, LOW);
        return 0;
    }
    int ledDash()
    {
        digitalWrite(_outputPin, HIGH);
        ledDelay();
        ledDelay();
        ledDelay();
        digitalWrite(_outputPin, LOW);
        return 0;
    }
    int ledSendMorse(const char message[])
    {
        //Unfortunately, you cannot use pointers to any class method like a
        //pointer to a function.
        //Fortunately, you can use a pointer to a static class method like a
        //pointer to a function.
        //So create static methods that call ledDelay, ledDot, and ledDash.
        //That is what s_ledDelay, s_ledDot, and s_ledDash are for.
        //The context will be the object calling ledSendMorse, so use "this"
        //which is a pointer to the object calling ledSendMorse.

        pinMode(_outputPin, OUTPUT);
        return sendMorse(message, s_ledDelay, s_ledDot, s_ledDash, this);
    }
    
    private:
    int _outputPin;
    int _dotDuration;
    
    //These static methods are what bridges the C++ programming style with the
    //C programming style of sendMorse(message, dly, dit, dah, context).
    static int s_ledDelay(void *context)
    {
        return static_cast<LEDMorseCodeMachine *>(context)->ledDelay();
    }
    static int s_ledDot(void *context)
    {
        return static_cast<LEDMorseCodeMachine *>(context)->ledDot();
    }
    static int s_ledDash(void *context)
    {
        return static_cast<LEDMorseCodeMachine *>(context)->ledDash();
    }
};

void setup()
{
    pinMode(_outputPin, OUTPUT);
}

void loop()
{
    //Create a slow Morse code machine.
    LEDMorseCodeMachine slow(LED_BUILTIN, 500);
    slow.ledSendMorse("abc");
    
    //Create a quick Morse code machine.
    LEDMorseCodeMachine quick(LED_BUILTIN, 100);
    quick.ledSendMorse("it's easy as 1 2 3");
}

