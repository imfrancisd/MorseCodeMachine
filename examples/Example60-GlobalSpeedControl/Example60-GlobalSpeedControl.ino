#include <MorseCodeMachine.h>

//You are going to control the speed of the Morse code with a global variable.
//This global variable will be used by the ledDelay, ledDot, and ledDash
//functions to control the durations of the dots, dashes, and the delays
//between the dots and dashes.
int dotDuration;

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

    //Notice how all of the functions below (sendSlowly, sendQuickly, ledDelay,
    //ledDot, and ledDash, are all accessing the dotDuration global variable.
    //
    //If the dotDuration global variable should somehow get an unexpected value
    //you will have to look at all the functions below to figure out where the
    //unexpected value came from.
    //
    //This is not a problem with a program this small. However, if the program
    //grows into thousands of lines long with hundreds of functions, then
    //figuring out what went wrong with a global variable can be difficult.
}

void sendSlowly()
{
    //Send "<SOS>" in Morse code slowly.
    //Modify the global variable dotDuration to equal 500.
    dotDuration = 500;
    sendMorse("<SOS>", ledDelay, ledDot, ledDash);
}

void sendQuickly()
{
    //Send "<SOS>" in Morse code quickly.
    //Modify the global variable dotDuration to equal 100.
    dotDuration = 100;
    sendMorse("<SOS>", ledDelay, ledDot, ledDash);
}

void ledDelay()
{
    //Wait for a small amount of time.
    //Look at the global variable dotDuration to figure out how long to delay.
    delay(dotDuration);
}

void ledDot()
{
    //Turn on the LED for a small amount of time, then turn off.
    //Look at the global variable dotDuration to figure out how long to turn on
    //the LED to make a dot.
    digitalWrite(LED_BUILTIN, HIGH);
    delay(dotDuration);
    digitalWrite(LED_BUILTIN, LOW);
}

void ledDash()
{
    //Turn on the LED three times as long as the dot, then turn off.
    //Look at the global variable dotDuration to figure out how long to turn on
    //the LED to make a dash.
    digitalWrite(LED_BUILTIN, HIGH);
    delay(dotDuration * 3);
    digitalWrite(LED_BUILTIN, LOW);
}

