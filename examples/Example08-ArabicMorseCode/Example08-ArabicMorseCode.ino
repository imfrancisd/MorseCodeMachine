#include <MorseCodeMachine.h>

//Create a character array that can store 100 characters.
//This will be used to hold the translation of the Arabic characters.
char morseArray[100];

void setup()
{
    //You are going to use the built-in LED in the Arduino to send Morse code.
    pinMode(LED_BUILTIN, OUTPUT);

    //Use the Serial monitor to look at the messages.
    Serial.begin(9600);
}

void loop()
{
    //You are going to send "مرحبا World!" as Morse code.
    //=========================================================================
    //Warning: Do not use accent marks on any Arabic character.
    //         Arabic Morse code does not use characters with accent marks.
    //
    //         See the following for more details about Arabic Morse code:
    //         Morse code for non-Latin alphabets - Wikipedia
    //         https://en.wikipedia.org/wiki/Morse_code_for_non-Latin_alphabets
    //
    //         Any unrecognized characters will be replaced with the Unicode
    //         replacement character (U+FFFD).
    //
    //         The following characters are recognized:
    //         Digits : 0123456789
    //         Symbols: "&'()+,-./:=?@
    //         Letters: AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz
    //                  ÀàÄäÅåĄąÆæĆćĈĉÇçÐðÉéÈèĘęĜĝĤĥĴĵŃńÑñÓóÖöŚśŜŝŠšÞþÜüŬŭŹźŻż
    //                  ﺍ ﺏ ﺕ ﺙ ﺝ ﺡ ﺥ ﺩ ﺫ ﺭ ﺯ ﺱ ﺵ ﺹ ﺽ ﻁ ﻅ ﻉ ﻍ ﻑ ﻕ ﻙ ﻝ ﻡ ﻥ ﻩ ﻭ ﻱ ﺀ
    //         Special: <>
    //         Space  :  
    //=========================================================================
    const char arabicMessage[] = "مرحبا World!";

    //Convert the Arabic message.
    //The 100 at the end tells convertMorseFromArabic that morseArray can only
    //hold 100 characters.
    int errorCode = convertMorseFromArabic(arabicMessage, morseArray, 100);

    //Check if there were any errors from convertMorseFromArabic.
    //convertMorseFromArabic returns 0 if there were no errors.
    if (errorCode == 0)
    {
        //Send the messages to the Serial Monitor to check the translation.
        Serial.println(arabicMessage);
        Serial.println(morseArray);
        
        //Since there were no errors, send Morse code using morseArray.
        sendMorse(morseArray, ledDelay, ledDot, ledDash);
    }
    else
    {
        //Send an error message to the Serial monitor.
        //The most likely reason an error happens is that the size of
        //morseArray is not big enough to contain the translation.
        Serial.println("There was an error translating this message:");
        Serial.println(arabicMessage);
    }
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

