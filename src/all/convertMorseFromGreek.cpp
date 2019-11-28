#include "convertMorseFromGreek.h"
#include "_skipDiacritic.h"
#include <stddef.h>

int convertMorseFromGreek(const char greekMessage[], char englishBuffer[], size_t englishBufferSize)
{
    if (!(greekMessage && englishBuffer && (englishBufferSize >= 1)))
    {
        return -1;
    }

    size_t i = 0;
    bool hasLetterSpacing = true;

    while (*greekMessage)
    {
        if ((*greekMessage & 0b10000000) == 0)
        {
            //Check for E or e (U+0045 or U+0065) followed by acute (U+0301).
            if (((greekMessage[0] == 'E') || (greekMessage[0] == 'e')) &&
                (((greekMessage[1] & 0xff) == 0xcc) && ((greekMessage[2] & 0xff) == 0x81)))
            {
                //Found E followed by acute.
                greekMessage += 3;
                
                //Check if there is another diacritic mark after acute.
                if (_skipDiacritic(&greekMessage))
                {
                    //Not E acute, but E acute followed by one or more diacritic.
                    while (_skipDiacritic(&greekMessage))
                        ;
                    englishBuffer[i++] = ' ';
                }
                else
                {
                    //Found E followed by acute only.
                    if ((i + 3) > englishBufferSize)
                    {
                        englishBuffer[i] = '\0';
                        return 1;
                    }
                    englishBuffer[i++] = 'E';
                    englishBuffer[i++] = 0xcc;
                    englishBuffer[i++] = 0x81;
                }
            }
            else
            {
                //Found ascii character.
                greekMessage++;

                //Check if there is a diacritic mark after ascii character.
                if (_skipDiacritic(&greekMessage))
                {
                    //Not ascii character, but ascii character followed by one or more diacritic.
                    while (_skipDiacritic(&greekMessage))
                        ;
                    englishBuffer[i++] = ' ';
                }
                else
                {
                    //Found ascii character.
                    if (greekMessage[-1] == '<')
                    {
                        hasLetterSpacing = false;
                    }
                    else if (greekMessage[-1] == '>')
                    {
                        hasLetterSpacing = true;
                    }
                    else
                    {
                        //Do nothing.
                    }
                    englishBuffer[i++] = greekMessage[-1];
                }
            }
        }

        if (i >= englishBufferSize)
        {
            englishBuffer[englishBufferSize - 1] = '\0';
            return 1;
        }
    }

    if (i >= englishBufferSize)
    {
        englishBuffer[englishBufferSize - 1] = '\0';
        return 1;
    }

    englishBuffer[i] = '\0';
    return 0;
}

