#include "MorseCodeMachine.h"

void setup()
{
    //You are going to use the built-in LED in the Arduino to send Morse code.
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    //You are going to send the prosign SOS as Morse code.
    //Notice how SOS is enclosed between <>.
    //This tells the sendMorse function to send the three letters as if they
    //were only one letter.
    //The distress signal will have this pattern:
    //    . . . - - - . . .
    //Notice how all the dots and dashes are spaced equally.
    sendMorse("<SOS>", ledDelay, ledDot, ledDash);

    //You are going to send SOS the wrong way.
    //Notice how SOS is NOT enclosed between <>.
    //This tells the sendMorse function to send three separate letters.
    //The pattern will be:
    //    . . .   - - -   . . .
    //Notice how dots and dashes are not spaced equally.
    //The two big gaps separates the three letters.
    sendMorse("SOS", ledDelay, ledDot, ledDash);

    //You are going to be creative and send the distress signal as EEETTTEEE.
    //Since E is a dot, and T is a dash, in theory you can send any Morse code
    //message you want just with those two letters, including SOS.
    //The pattern of EEETTTEEE sent as a single patterns is:
    //    . . . - - - . . .
    //Notice how it looks just like the distress pattern SOS.
    sendMorse("<EEETTTEEE>", ledDelay, ledDot, ledDash);
}

//Create a delay function and give it to the sendMorse function so that the
//sendMorse function can space out the letters and the words properly.
//You can give this function any name you want.
void ledDelay()
{
    //Wait for a small amount of time.
    delay(200);
}

//Create a dot function and give it to the sendMorse function so that the
//sendMorse function can create dots.
//You can give this function any name you want.
void ledDot()
{
    //Turn on the LED for a small amount of time, then turn off.
    digitalWrite(LED_BUILTIN, HIGH);
    ledDelay();
    digitalWrite(LED_BUILTIN, LOW);
}

//Create a dash function and give it to the sendMorse function so that the
//sendMorse function can create dashes.
//You can give this function any name you want.
void ledDash()
{
    //Turn on the LED three times as long as the dot, then turn off.
    digitalWrite(LED_BUILTIN, HIGH);
    ledDelay();
    ledDelay();
    ledDelay();
    digitalWrite(LED_BUILTIN, LOW);
}
