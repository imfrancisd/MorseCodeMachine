#include "MorseCodeMachine.h"

void setup()
{
    //You are going to use the Arduino IDE Serial Monitor
    //to see Morse code as a series of "dit" and "dah".
    Serial.begin(9600);
}

void loop()
{
    //You are going to send the distress signal SOS as Morse code to
    //the serial monitor as a series of "dit" and "dah".
    //You will tell the sendMorse function how to make dots and dashes
    //outside this function.
    int errorCode = sendMorse("<sos>", serialDelay, serialDot, serialDash);

    //Print a new line.
    Serial.println("");

    //Check if there was any error sending the Morse code.
    if (errorCode != 0)
    {
        Serial.println("Uh oh, the Morse code was not sent.");
        Serial.print("The error code was: ");
        Serial.println(errorCode);
    }
    else
    {
        Serial.println("The message was sent.");
        Serial.print("The error code was: ");
        Serial.println(errorCode);
    }
}

//Create a delay function and give it to the sendMorse function so that the
//sendMorse function can space out the letters and the words properly.
//You can give this function any name you want.
//
//Notice that unlike the other examples, the function starts with int.
//This means that the function will return an integer when the function is
//finished.
//
//The sendMorse function will interpret the returned integer as an error
//code. Any non-zero integer will be interpreted by sendMorse as an error
//and will cause the sendMorse function to stop immediately.
int serialDelay()
{
    //Space between dots and dashes.
    Serial.print("_");

    //Wait for a small amount of time.
    delay(250);

    //Return 0 to tell the sendMorse function that there were no errors.
    return 0;
}

//Create a dot function and give it to the sendMorse function so that the
//sendMorse function can create dots.
//You can give this function any name you want.
//
//Notice that unlike the other examples, the function starts with int.
//This means that the function will return an integer when the function is
//finished.
//
//The sendMorse function will interpret the returned integer as an error
//code. Any non-zero integer will be interpreted by sendMorse as an error
//and will cause the sendMorse function to stop immediately.
int serialDot()
{
    //Send the characters "dit" for the dot.
    Serial.print("dit");

    //Wait the same amount of time as the delay.
    delay(250);

    //Simulate an error by choosing randomly choosing a number between 1-100.
    //If you get a number greater than 95, return that number as the error code.
    //If you get a number less than or equal to 95, return 0.

    int simulateError = random(1, 101);
    if (simulateError > 95)
    {
        return simulateError;
    }
    else
    {
        return 0;
    }
}

//Create a dash function and give it to the sendMorse function so that the
//sendMorse function can create dashes.
//You can give this function any name you want.
//
//Notice that unlike the other examples, the function starts with int.
//This means that the function will return an integer when the function is
//finished.
//
//The sendMorse function will interpret the returned integer as an error
//code. Any non-zero integer will be interpreted by sendMorse as an error
//and will cause the sendMorse function to stop immediately.
int serialDash()
{
    //Send the characters "dah" for the dash.
    Serial.print("dah");

    //Wait three times as long as the delay.
    delay(750);

    //Simulate an error by choosing randomly choosing a number between 1-100.
    //If you get a number greater than 95, return that number as the error code.
    //If you get a number less than or equal to 95, return 0.

    int simulateError = random(1, 101);
    if (simulateError > 95)
    {
        return simulateError;
    }
    else
    {
        return 0;
    }
}
