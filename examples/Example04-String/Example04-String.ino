#include <MorseCodeMachine.h>

//Store Morse code as a series of "dit" and "dah" inside a String object.
String morseCode = "";

void setup()
{
    //You are going to use the Arduino IDE Serial Monitor to see Morse code as
    //a series of "dit" and "dah" inside a String object.
    Serial.begin(9600);
}

void loop()
{
    //You are going to convert "<SOS>" to Morse code as a series of "dit" and
    //"dah", and store the "dit" and "dah" inside a String object.
    //You will tell the sendMorse function how to make dots and dashes
    //outside this function.
    sendMorse("<SOS>", stringDelay, stringDot, stringDash);

    //See the Morse code inside the String object using the Arduino IDE Serial
    //Monitor.
    Serial.println(morseCode);

    //Clear the String object so it does not keep getting longer as the loop()
    //function is repeated.
    morseCode = "";

    //Wait for a small amount of time so that the Serial Monitor does not
    //scroll too fast.
    delay(1000);
}

//Create a delay function and give it to the sendMorse function so that the
//sendMorse function can space out the letters and the words properly.
//You can give this function any name you want.
void stringDelay()
{
    //Store a "_" to space dots and dashes inside the String object.
    morseCode += "_";
}

//Create a dot function and give it to the sendMorse function so that the
//sendMorse function can create dots.
//You can give this function any name you want.
void stringDot()
{
    //Store the characters "dit" for the dot inside the String object.
    morseCode += "dit";
}

//Create a dash function and give it to the sendMorse function so that the
//sendMorse function can create dashes.
//You can give this function any name you want.
void stringDash()
{
    //Store the characters "dah" for the dash inside the String object.
    morseCode += "dah";
}

