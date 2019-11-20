#include <MorseCodeMachine.h>

void setup()
{
    //You are going to use the built-in LED in the Arduino to send Morse code.
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    //The sendSlowly function below will send the Morse code slowly.
    sendSlowly();
    
    //The sendQuickly function below will send the Morse code quickly.
    sendQuickly();
}

void sendSlowly()
{
    //Send "<SOS>" in Morse code slowly.
    //Create a local variable dotDuration and make it equal to 500.
    //
    //None of the other functions can read or write to this local variable
    //unless you give the other functions a pointer to dotDuration.
    //
    //Notice the "&dotDuration". That is the pointer to dotDuration, and the
    //pointer to dotDuration is given to the sendMorse function. The sendMorse
    //function will then send that pointer to ledDelay, ledDot, and ledDash
    //functions. How do I know? Because I wrote sendMorse to do that.

    int dotDuration = 500;
    sendMorse("<SOS>", ledDelay, ledDot, ledDash, &dotDuration);
}

void sendQuickly()
{
    //Send "<SOS>" in Morse code quickly.
    //Create a local variable dotDuration and make it equal to 100.
    //
    //None of the other functions can read or write to this local variable
    //unless you give the other functions a pointer to dotDuration.
    //
    //Notice the "&dotDuration". That is the pointer to dotDuration, and the
    //pointer to dotDuration is given to the sendMorse function. The sendMorse
    //function will then send that pointer to ledDelay, ledDot, and ledDash
    //functions. How do I know? Because I wrote sendMorse to do that.

    int dotDuration = 100;
    sendMorse("<SOS>", ledDelay, ledDot, ledDash, &dotDuration);
}

void ledDelay(void *context)
{
    //Wait for a small amount of time.
    //
    //Notice that unlike the previous examples, the delay function now has
    //a parameter "void *context". "void *" just means that the parameter is
    //a pointer to any type of data. In this particular case, the pointer is
    //given to ledDelay by the sendMorse function, which was given to the
    //sendMorse function by the sendSlowly and sendQuickly functions, which is
    //a pointer to an integer representing the dot duration.

    //Extract the actual integer value from the void * pointer.

    //First convert "void *context" to "int *pointerToInt" which is a pointer
    //to an integer.
    int *pointerToInt = static_cast<int *>(context);

    //Then get the actual integer by using "*" in "*pointerToInt".
    int dotDuration = *pointerToInt;

    //Now, use that integer value to delay.
    delay(dotDuration);
}

void ledDot(void *context)
{
    //Turn on the LED for a small amount of time, then turn off.
    digitalWrite(LED_BUILTIN, HIGH);

    //You can also extract the integer value from "void *context" in one line.
    delay(*static_cast<int *>(context));
    
    digitalWrite(LED_BUILTIN, LOW);
}

void ledDash(void *context)
{
    //Turn on the LED three times as long as the dot, then turn off.
    digitalWrite(LED_BUILTIN, HIGH);

    //Instead of extracting the integer value from "void *context" and calling
    //delay, you can also call ledDelay and give ledDelay the "void *context".
    ledDelay(context);
    ledDelay(context);
    ledDelay(context);

    digitalWrite(LED_BUILTIN, LOW);
}

