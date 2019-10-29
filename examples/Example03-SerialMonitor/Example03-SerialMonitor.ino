#include "MorseCodeMachine.h"

void setup()
{
    //You are going to use the Arduino IDE Serial Monitor
    //to see Morse code as a series of "dit" and "dah".
    Serial.begin(9600);
}

void loop()
{
    //You are going to send "Hello World" as Morse code to the serail
    //monitor as a series of "dit" and "dah".
    //You will tell the sendMorse function how to make dots and dashes
    //outside this function.
    sendMorse("Hello World", serialDelay, serialDot, serialDash);

    //Print a new line.
    Serial.println("");
}

//Create a delay function and give it to the sendMorse function so that the
//sendMorse function can space out the letters and the words properly.
//You can give this function any name you want.
void serialDelay()
{
    //Space between dots and dashes.
    Serial.print(" ");

    //Wait for a small amount of time.
    delay(250);
}

//Create a dot function and give it to the sendMorse function so that the
//sendMorse function can create dots.
//You can give this function any name you want.
void serialDot()
{
    //Send the characters "dit" for the dot.
    Serial.print("dit");

    //Wait the same amount of time as the delay.
    delay(250);
}

//Create a dash function and give it to the sendMorse function so that the
//sendMorse function can create dashes.
//You can give this function any name you want.
void serialDash()
{
    //Send the characters "dah" for the dash.
    Serial.print("dah");

    //Wait three times as long as the delay.
    delay(750);
}
