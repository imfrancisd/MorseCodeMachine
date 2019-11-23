#include "sendMorse.h"
#include "_enToMorseElements.h"

void sendMorse(const char message[], void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    if (!(message && delayFunction && dotFunction && dashFunction))
    {
        return;
    }

    bool hasLetterSpacing = true;
    bool wasPrevCharSpace = true;

    while (true)
    {
        char c = *message;
        unsigned int morseElements = _enToMorseElements(&message);

        if (c == '<')
        {
            //Delay between characters is equal to the duration of the delay between dit/dah.
            hasLetterSpacing = false;
        }
        else if (c == '>')
        {
            //Delay between characters is greater than the duration of the delay between dit/dah.
            hasLetterSpacing = true;
        }
        else if (morseElements)
        {
            //Generate dit/dah.
            while (morseElements & 0b1000000000000000)
            {
                if (morseElements & 0b0000000010000000)
                {
                    dashFunction();
                }
                else
                {
                    dotFunction();
                }

                //Delay between dit/dah.
                delayFunction();

                morseElements <<= 1;
            }

            wasPrevCharSpace = false;
        }
        else if (hasLetterSpacing)
        {
            //Delay between words, including the '\0'.
            //7 delays total.
            //3 from previous letter, 2 from here, 2 at end of loop,
            //or if no previous letter, 5 delays here, 2 at end of loop.
            for (int i = (wasPrevCharSpace ? 5 : 2); i > 0; i--)
            {
                delayFunction();
            }

            wasPrevCharSpace = true;
        }

        if (hasLetterSpacing)
        {
            //Delay between characters.
            //3 delays total. 1 from end of character, 2 from here.
            for (int i = 2; i > 0; i--)
            {
                delayFunction();
            }
        }

        if (c == '\0')
        {
            break;
        }
    }
}

void sendMorse(const char message[], void (*delayFunction)(void *context), void (*dotFunction)(void *context), void (*dashFunction)(void *context), void *context)
{
    if (!(message && delayFunction && dotFunction && dashFunction))
    {
        return;
    }

    bool hasLetterSpacing = true;
    bool wasPrevCharSpace = true;

    while (true)
    {
        char c = *message;
        unsigned int morseElements = _enToMorseElements(&message);

        if (c == '<')
        {
            //Delay between characters is equal to the duration of the delay between dit/dah.
            hasLetterSpacing = false;
        }
        else if (c == '>')
        {
            hasLetterSpacing = true;
        }
        else if (morseElements)
        {
            //Generate dit/dah.
            while (morseElements & 0b1000000000000000)
            {
                if (morseElements & 0b0000000010000000)
                {
                    dashFunction(context);
                }
                else
                {
                    dotFunction(context);
                }

                //Delay between dit/dah.
                delayFunction(context);

                morseElements <<= 1;
            }

            wasPrevCharSpace = false;
        }
        else if (hasLetterSpacing)
        {
            //Delay between words, including the '\0'.
            //7 delays total.
            //3 from previous letter, 2 from here, 2 at end of loop,
            //or if no previous letter, 5 delays here, 2 at end of loop.
            for (int i = (wasPrevCharSpace ? 5 : 2); i > 0; i--)
            {
                delayFunction(context);
            }

            wasPrevCharSpace = true;
        }

        if (hasLetterSpacing)
        {
            //Delay between characters.
            //3 delays total. 1 from end of character, 2 from here.
            for (int i = 2; i > 0; i--)
            {
                delayFunction(context);
            }
        }

        if (c == '\0')
        {
            break;
        }
    }
}

int sendMorse(const char message[], int (*delayFunction)(), int (*dotFunction)(), int (*dashFunction)())
{
    if (!(message && delayFunction && dotFunction && dashFunction))
    {
        return -1;
    }

    int errorCode = 0;
    bool hasLetterSpacing = true;
    bool wasPrevCharSpace = true;

    while (true)
    {
        char c = *message;
        unsigned int morseElements = _enToMorseElements(&message);

        if (c == '<')
        {
            //Delay between characters is equal to the duration of the delay between dit/dah.
            hasLetterSpacing = false;
        }
        else if (c == '>')
        {
            //Delay between characters is greater than the duration of the delay between dit/dah.
            hasLetterSpacing = true;
        }
        else if (morseElements)
        {
            //Generate dit/dah.
            while (morseElements & 0b1000000000000000)
            {
                if (morseElements & 0b0000000010000000)
                {
                    errorCode = dashFunction();
                    if (errorCode)
                    {
                        return errorCode;
                    }
                }
                else
                {
                    errorCode = dotFunction();
                    if (errorCode)
                    {
                        return errorCode;
                    }
                }

                //Delay between dit/dah.
                errorCode = delayFunction();
                if (errorCode)
                {
                    return errorCode;
                }

                morseElements <<= 1;
            }

            wasPrevCharSpace = false;
        }
        else if (hasLetterSpacing)
        {
            //Delay between words, including the '\0'.
            //7 delays total.
            //3 from previous letter, 2 from here, 2 at end of loop,
            //or if no previous letter, 5 delays here, 2 at end of loop.
            for (int i = (wasPrevCharSpace ? 5 : 2); i > 0; i--)
            {
                errorCode = delayFunction();
                if (errorCode)
                {
                    return errorCode;
                }
            }

            wasPrevCharSpace = true;
        }

        if (hasLetterSpacing)
        {
            //Delay between characters.
            //3 delays total. 1 from end of character, 2 from here.
            for (int i = 2; i > 0; i--)
            {
                errorCode = delayFunction();
                if (errorCode)
                {
                    return errorCode;
                }
            }
        }

        if (c == '\0')
        {
            break;
        }
    }

    return 0;
}

int sendMorse(const char message[], int (*delayFunction)(void *context), int (*dotFunction)(void *context), int (*dashFunction)(void *context), void *context)
{
    if (!(message && delayFunction && dotFunction && dashFunction))
    {
        return -1;
    }

    int errorCode = 0;
    bool hasLetterSpacing = true;
    bool wasPrevCharSpace = true;

    while (true)
    {
        char c = *message;
        unsigned int morseElements = _enToMorseElements(&message);

        if (c == '<')
        {
            //Delay between characters is equal to the duration of the delay between dit/dah.
            hasLetterSpacing = false;
        }
        else if (c == '>')
        {
            //Delay between characters is greater than the duration of the delay between dit/dah.
            hasLetterSpacing = true;
        }
        else if (morseElements)
        {
            //Generate dit/dah.
            while (morseElements & 0b1000000000000000)
            {
                if (morseElements & 0b0000000010000000)
                {
                    errorCode = dashFunction(context);
                    if (errorCode)
                    {
                        return errorCode;
                    }
                }
                else
                {
                    errorCode = dotFunction(context);
                    if (errorCode)
                    {
                        return errorCode;
                    }
                }

                //Delay between dit/dah.
                errorCode = delayFunction(context);
                if (errorCode)
                {
                    return errorCode;
                }

                morseElements <<= 1;
            }

            wasPrevCharSpace = false;
        }
        else if (hasLetterSpacing)
        {
            //Delay between words, including the '\0'.
            //7 delays total.
            //3 from previous letter, 2 from here, 2 at end of loop,
            //or if no previous letter, 5 delays here, 2 at end of loop.
            for (int i = (wasPrevCharSpace ? 5 : 2); i > 0; i--)
            {
                errorCode = delayFunction(context);
                if (errorCode)
                {
                    return errorCode;
                }
            }

            wasPrevCharSpace = true;
        }

        if (hasLetterSpacing)
        {
            //Delay between characters.
            //3 delays total. 1 from end of character, 2 from here.
            for (int i = 2; i > 0; i--)
            {
                errorCode = delayFunction(context);
                if (errorCode)
                {
                    return errorCode;
                }
            }
        }

        if (c == '\0')
        {
            break;
        }
    }

    return 0;
}

