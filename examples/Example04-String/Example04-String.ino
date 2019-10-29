#include "MorseCodeMachine.h"

//Store Morse code as a series of "dit" and "dah" inside
//a String object.
String MorseCode = "";

void setup()
{
    //You are going to use the Arduino IDE Serial Monitor
    //to see Morse code as a series of "dit" and "dah"
    //from a String object.
    Serial.begin(9600);
}

void loop()
{
    //You are going to convert "Hello World" to Morse code as a
    //series of "dit" and "dah" and store the "dit" and "dah" inside
    //a String ojbect.
    //You will tell the sendMorse function how to make dots and dashes
    //outside this function.
    sendMorse("Hello World", stringDelay, stringDot, stringDash);

    //See the Morse code inside the String object using the
    //Arduino IDE Serial Monitor.
    Serial.println(MorseCode);

    //Clear the String object so it does not keep getting longer as the
    //loop() function is repeated.
    MorseCode = "";

    //Wait a little bit so the Serial Monitor does not scroll too fast.
    delay(1000);
}

//Create a delay function and give it to the sendMorse function so that the
//sendMorse function can space out the letters and the words properly.
//You can give this function any name you want.
void stringDelay()
{
    //Store a space between dots and dashes inside the String object.
    MorseCode += " ";
}

//Create a dot function and give it to the sendMorse function so that the
//sendMorse function can create dots.
//You can give this function any name you want.
void stringDot()
{
    //Store the characters "dit" for the dot inside the String object.
    MorseCode += "dit";
}

//Create a dash function and give it to the sendMorse function so that the
//sendMorse function can create dashes.
//You can give this function any name you want.
void stringDash()
{
    //Store the characters "dah" for the dash inside the String object.
    MorseCode += "dah";
}
