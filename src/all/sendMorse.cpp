#include "sendMorse.h"

static unsigned int charToMorseElements(char c);

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
        unsigned int morseElements = charToMorseElements(*message);
        if ((message[0] == (char)0xc3) && ((message[1] == (char)0x89) || (message[1] == (char)0xa9)))
        {
            //Accute E
            morseElements = 0b1111100000100000;
            message++;
        }

        if (*message == '<')
        {
            hasLetterSpacing = false;
        }
        else if (*message == '>')
        {
            hasLetterSpacing = true;
        }
        else if (morseElements)
        {
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

        if (*message == '\0')
        {
            break;
        }
        
        message++;
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
        unsigned int morseElements = charToMorseElements(*message);
        if ((message[0] == (char)0xc3) && ((message[1] == (char)0x89) || (message[1] == (char)0xa9)))
        {
            //Accute E
            morseElements = 0b1111100000100000;
            message++;
        }

        if (*message == '<')
        {
            hasLetterSpacing = false;
        }
        else if (*message == '>')
        {
            hasLetterSpacing = true;
        }
        else if (morseElements)
        {
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

        if (*message == '\0')
        {
            break;
        }
        
        message++;
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
        unsigned int morseElements = charToMorseElements(*message);
        if ((message[0] == (char)0xc3) && ((message[1] == (char)0x89) || (message[1] == (char)0xa9)))
        {
            //Accute E
            morseElements = 0b1111100000100000;
            message++;
        }

        if (*message == '<')
        {
            hasLetterSpacing = false;
        }
        else if (*message == '>')
        {
            hasLetterSpacing = true;
        }
        else if (morseElements)
        {
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

        if (*message == '\0')
        {
            break;
        }
        
        message++;
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
        unsigned int morseElements = charToMorseElements(*message);
        if ((message[0] == (char)0xc3) && ((message[1] == (char)0x89) || (message[1] == (char)0xa9)))
        {
            //Accute E
            morseElements = 0b1111100000100000;
            message++;
        }

        if (*message == '<')
        {
            hasLetterSpacing = false;
        }
        else if (*message == '>')
        {
            hasLetterSpacing = true;
        }
        else if (morseElements)
        {
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

        if (*message == '\0')
        {
            break;
        }
        
        message++;
    }

    return 0;
}

static unsigned int charToMorseElements(char c)
{
    //16-bit return value format:
    //aaaaaaa0bbbbbbb0
    //aaaaaaa0 = number of morse elements as a series of 1
    //bbbbbbb0 = morse elements as a series of 0 1, 0 is dit, 1 is dah
    //
    //Example:
    //char '1' is morse dit dah dah dah dah
    //aaaaaaa0 = 11111000 (5 morse elements, 5 1 starting from msb)
    //bbbbbbb0 = 01111000 (dit dah dah dah dah)
    //1111100001111000

    switch (c)
    {
        //Digits 0-9.

        case '0':
            //DAH DAH DAH DAH DAH
            return 0b1111100011111000;

        case '1':
            //DIT DAH DAH DAH DAH
            return 0b1111100001111000;

        case '2':
            //DIT DIT DAH DAH DAH
            return 0b1111100000111000;

        case '3':
            //DIT DIT DIT DAH DAH
            return 0b1111100000011000;

        case '4':
            //DIT DIT DIT DIT DAH
            return 0b1111100000001000;

        case '5':
            //DIT DIT DIT DIT DIT
            return 0b1111100000000000;

        case '6':
            //DAH DIT DIT DIT DIT
            return 0b1111100010000000;

        case '7':
            //DAH DAH DIT DIT DIT
            return 0b1111100011000000;

        case '8':
            //DAH DAH DAH DIT DIT
            return 0b1111100011100000;

        case '9':
            //DAH DAH DAH DAH DIT
            return 0b1111100011110000;

        //Letters A-z and a-z.

        case 'A':
        case 'a':
            //DIT DAH
            return 0b1100000001000000;

        case 'B':
        case 'b':
            //DAH DIT DIT DIT
            return 0b1111000010000000;

        case 'C':
        case 'c':
            //DAH DIT DAH DIT
            return 0b1111000010100000;

        case 'D':
        case 'd':
            //DAH DIT DIT
            return 0b1110000010000000;

        case 'E':
        case 'e':
            //DIT
            return 0b1000000000000000;

        case 'F':
        case 'f':
            //DIT DIT DAH DIT
            return 0b1111000000100000;

        case 'G':
        case 'g':
            //DAH DAH DIT
            return 0b1110000011000000;

        case 'H':
        case 'h':
            //DIT DIT DIT DIT
            return 0b1111000000000000;

        case 'I':
        case 'i':
            //DIT DIT
            return 0b1100000000000000;

        case 'J':
        case 'j':
            //DIT DAH DAH DAH
            return 0b1111000001110000;

        case 'K':
        case 'k':
            //DAH DIT DAH
            return 0b1110000010100000;

        case 'L':
        case 'l':
            //DIT DAH DIT DIT
            return 0b1111000001000000;

        case 'M':
        case 'm':
            //DAH DAH
            return 0b1100000011000000;

        case 'N':
        case 'n':
            //DAH DIT
            return 0b1100000010000000;

        case 'O':
        case 'o':
            //DAH DAH DAH
            return 0b1110000011100000;

        case 'P':
        case 'p':
            //DIT DAH DAH DIT
            return 0b1111000001100000;

        case 'Q':
        case 'q':
            //DAH DAH DIT DAH
            return 0b1111000011010000;

        case 'R':
        case 'r':
            //DIT DAH DIT
            return 0b1110000001000000;

        case 'S':
        case 's':
            //DIT DIT DIT
            return 0b1110000000000000;

        case 'T':
        case 't':
            //DAH
            return 0b1000000010000000;

        case 'U':
        case 'u':
            //DIT DIT DAH
            return 0b1110000000100000;

        case 'V':
        case 'v':
            //DIT DIT DIT DAH
            return 0b1111000000010000;

        case 'W':
        case 'w':
            //DIT DAH DAH
            return 0b1110000001100000;

        case 'X':
        case 'x':
            //DAH DIT DIT DAH
            return 0b1111000010010000;

        case 'Y':
        case 'y':
            //DAH DIT DAH DAH
            return 0b1111000010110000;

        case 'Z':
        case 'z':
            //DAH DAH DIT DIT
            return 0b1111000011000000;

        //Symbols.

        case '"':
            //DIT DAH DIT DIT DAH DIT
            return 0b1111110001001000;

        case '&':
            //DIT DAH DIT DIT DIT
            return 0b1111100001000000;

        case '\'':
            //DIT DAH DAH DAH DAH DIT
            return 0b1111110001111000;

        case '(':
            //DAH DIT DAH DAH DIT
            return 0b1111100010110000;

        case ')':
            //DAH DIT DAH DAH DIT DAH
            return 0b1111110010110100;

        case '+':
            //DIT DAH DIT DAH DIT
            return 0b1111100001010000;

        case ',':
            //DAH DAH DIT DIT DAH DAH
            return 0b1111110011001100;

        case '-':
            //DAH DIT DIT DIT DIT DAH
            return 0b1111110010000100;

        case '.':
            //DIT DAH DIT DAH DIT DAH
            return 0b1111110001010100;

        case '/':
            //DAH DIT DIT DAH DIT
            return 0b1111100010010000;

        case ':':
            //DAH DAH DAH DIT DIT DIT
            return 0b1111110011100000;

        case '=':
            //DAH DIT DIT DIT DAH
            return 0b1111100010001000;

        case '?':
            //DIT DIT DAH DAH DIT DIT
            return 0b1111110000110000;

        case '@':
            //DIT DAH DAH DIT DAH DIT
            return 0b1111110001101000;

        case ' ':
        case '<':
        case '>':
        default:
            return 0;
    }
}

