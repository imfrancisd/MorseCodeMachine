#include "sendMorse.h"

static unsigned char charToMorseElements(char c, int &elementCount);

void sendMorse(const char message[], void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    if (!(message && delayFunction && dotFunction && dashFunction))
    {
        return;
    }

    bool hasLetterSpacing = true;

    while (true)
    {
        int morseElementCount = 0;
        unsigned char morseElements = charToMorseElements(*message, morseElementCount);

        if (*message == '<')
        {
            //Special character for this library.
            //Do not put delay between letters.
            hasLetterSpacing = false;
        }
        else if (*message == '>')
        {
            //Special character for this library.
            //Put delay between letters.
            hasLetterSpacing = true;
        }
        else if (morseElementCount > 0)
        {
            for (int i = morseElementCount; i > 0; i--)
            {
                if (morseElements & 1)
                {
                    dashFunction();
                    delayFunction();
                }
                else
                {
                    dotFunction();
                    delayFunction();
                }
                morseElements >>= 1;
            }
        }
        else
        {
            //Make everything else a delay between words, including the '\0'.
            //7 delays total. 3 from previous letter, 2 from here, 2 at end of loop.
            delayFunction();
            delayFunction();
        }

        if (hasLetterSpacing)
        {
            //Delay between digits and letters.
            //3 delays total. 1 from end of digit/letter, 2 from here.
            delayFunction();
            delayFunction();
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

    while (true)
    {
        int morseElementCount = 0;
        unsigned char morseElements = charToMorseElements(*message, morseElementCount);

        if (*message == '<')
        {
            //Special character for this library.
            //Do not put delay between letters.
            hasLetterSpacing = false;
        }
        else if (*message == '>')
        {
            //Special character for this library.
            //Put delay between letters.
            hasLetterSpacing = true;
        }
        else if (morseElementCount > 0)
        {
            for (int i = morseElementCount; i > 0; i--)
            {
                if (morseElements & 1)
                {
                    dashFunction(context);
                    delayFunction(context);
                }
                else
                {
                    dotFunction(context);
                    delayFunction(context);
                }
                morseElements >>= 1;
            }
        }
        else
        {
            //Make everything else a delay between words, including the '\0'.
            //7 delays total. 3 from previous letter, 2 from here, 2 at end of loop.
            delayFunction(context);
            delayFunction(context);
        }

        if (hasLetterSpacing)
        {
            //Delay between digits and letters.
            //3 delays total. 1 from end of digit/letter, 2 from here.
            delayFunction(context);
            delayFunction(context);
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

    bool hasLetterSpacing = true;

    while (true)
    {
        int errorCode = 0;
        int morseElementCount = 0;
        unsigned char morseElements = charToMorseElements(*message, morseElementCount);

        if (*message == '<')
        {
            //Special character for this library.
            //Do not put delay between letters.
            hasLetterSpacing = false;
        }
        else if (*message == '>')
        {
            //Special character for this library.
            //Put delay between letters.
            hasLetterSpacing = true;
        }
        else if (morseElementCount > 0)
        {
            for (int i = morseElementCount; i > 0; i--)
            {
                if (morseElements & 1)
                {
                    errorCode = dashFunction();
                    if (errorCode)
                    {
                        return errorCode;
                    }
                    errorCode = delayFunction();
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
                    errorCode = delayFunction();
                    if (errorCode)
                    {
                        return errorCode;
                    }
                }
                morseElements >>= 1;
            }
        }
        else
        {
            //Make everything else a delay between words, including the '\0'.
            //7 delays total. 3 from previous letter, 2 from here, 2 at end of loop.
            errorCode = delayFunction();
            if (errorCode)
            {
                return errorCode;
            }
            errorCode = delayFunction();
            if (errorCode)
            {
                return errorCode;
            }
        }

        if (hasLetterSpacing)
        {
            //Delay between digits and letters.
            //3 delays total. 1 from end of digit/letter, 2 from here.
            errorCode = delayFunction();
            if (errorCode)
            {
                return errorCode;
            }
            errorCode = delayFunction();
            if (errorCode)
            {
                return errorCode;
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

    bool hasLetterSpacing = true;

    while (true)
    {
        int errorCode = 0;
        int morseElementCount = 0;
        unsigned char morseElements = charToMorseElements(*message, morseElementCount);

        if (*message == '<')
        {
            //Special character for this library.
            //Do not put delay between letters.
            hasLetterSpacing = false;
        }
        else if (*message == '>')
        {
            //Special character for this library.
            //Put delay between letters.
            hasLetterSpacing = true;
        }
        else if (morseElementCount > 0)
        {
            for (int i = morseElementCount; i > 0; i--)
            {
                if (morseElements & 1)
                {
                    errorCode = dashFunction(context);
                    if (errorCode)
                    {
                        return errorCode;
                    }
                    errorCode = delayFunction(context);
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
                    errorCode = delayFunction(context);
                    if (errorCode)
                    {
                        return errorCode;
                    }
                }
                morseElements >>= 1;
            }
        }
        else
        {
            //Make everything else a delay between words, including the '\0'.
            //7 delays total. 3 from previous letter, 2 from here, 2 at end of loop.
            errorCode = delayFunction(context);
            if (errorCode)
            {
                return errorCode;
            }
            errorCode = delayFunction(context);
            if (errorCode)
            {
                return errorCode;
            }
        }

        if (hasLetterSpacing)
        {
            //Delay between digits and letters.
            //3 delays total. 1 from end of digit/letter, 2 from here.
            errorCode = delayFunction(context);
            if (errorCode)
            {
                return errorCode;
            }
            errorCode = delayFunction(context);
            if (errorCode)
            {
                return errorCode;
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

static unsigned char charToMorseElements(char c, int &elementCount)
{
    switch (c)
    {
        //Digits 0-9.

        case '0':
            //DAH DAH DAH DAH DAH
            elementCount = 5;
            return 0b11111;

        case '1':
            //DIT DAH DAH DAH DAH
            elementCount = 5;
            return 0b11110;

        case '2':
            //DIT DIT DAH DAH DAH
            elementCount = 5;
            return 0b11100;

        case '3':
            //DIT DIT DIT DAH DAH
            elementCount = 5;
            return 0b11000;

        case '4':
            //DIT DIT DIT DIT DAH
            elementCount = 5;
            return 0b10000;

        case '5':
            //DIT DIT DIT DIT DIT
            elementCount = 5;
            return 0b00000;

        case '6':
            //DAH DIT DIT DIT DIT
            elementCount = 5;
            return 0b00001;

        case '7':
            //DAH DAH DIT DIT DIT
            elementCount = 5;
            return 0b00011;

        case '8':
            //DAH DAH DAH DIT DIT
            elementCount = 5;
            return 0b00111;

        case '9':
            //DAH DAH DAH DAH DIT
            elementCount = 5;
            return 0b01111;

        //Letters A-z and a-z.

        case 'A':
        case 'a':
            //DIT DAH
            elementCount = 2;
            return 0b10;

        case 'B':
        case 'b':
            //DAH DIT DIT DIT
            elementCount = 4;
            return 0b0001;

        case 'C':
        case 'c':
            //DAH DIT DAH DIT
            elementCount = 4;
            return 0b0101;

        case 'D':
        case 'd':
            //DAH DIT DIT
            elementCount = 3;
            return 0b001;

        case 'E':
        case 'e':
            //DIT
            elementCount = 1;
            return 0b0;

        case 'F':
        case 'f':
            //DIT DIT DAH DIT
            elementCount = 4;
            return 0b0100;

        case 'G':
        case 'g':
            //DAH DAH DIT
            elementCount = 3;
            return 0b011;

        case 'H':
        case 'h':
            //DIT DIT DIT DIT
            elementCount = 4;
            return 0b0000;

        case 'I':
        case 'i':
            //DIT DIT
            elementCount = 2;
            return 0b00;

        case 'J':
        case 'j':
            //DIT DAH DAH DAH
            elementCount = 4;
            return 0b1110;

        case 'K':
        case 'k':
            //DAH DIT DAH
            elementCount = 3;
            return 0b101;

        case 'L':
        case 'l':
            //DIT DAH DIT DIT
            elementCount = 4;
            return 0b0010;

        case 'M':
        case 'm':
            //DAH DAH
            elementCount = 2;
            return 0b11;

        case 'N':
        case 'n':
            //DAH DIT
            elementCount = 2;
            return 0b01;

        case 'O':
        case 'o':
            //DAH DAH DAH
            elementCount = 3;
            return 0b111;

        case 'P':
        case 'p':
            //DIT DAH DAH DIT
            elementCount = 4;
            return 0b0110;

        case 'Q':
        case 'q':
            //DAH DAH DIT DAH
            elementCount = 4;
            return 0b1011;

        case 'R':
        case 'r':
            //DIT DAH DIT
            elementCount = 3;
            return 0b010;

        case 'S':
        case 's':
            //DIT DIT DIT
            elementCount = 3;
            return 0b000;

        case 'T':
        case 't':
            //DAH
            elementCount = 1;
            return 0b1;

        case 'U':
        case 'u':
            //DIT DIT DAH
            elementCount = 3;
            return 0b100;

        case 'V':
        case 'v':
            //DIT DIT DIT DAH
            elementCount = 4;
            return 0b1000;

        case 'W':
        case 'w':
            //DIT DAH DAH
            elementCount = 3;
            return 0b110;

        case 'X':
        case 'x':
            //DAH DIT DIT DAH
            elementCount = 4;
            return 0b1001;

        case 'Y':
        case 'y':
            //DAH DIT DAH DAH
            elementCount = 4;
            return 0b1101;

        case 'Z':
        case 'z':
            //DAH DAH DIT DIT
            elementCount = 4;
            return 0b0011;

        //Symbols.

        case '"':
            //DIT DAH DIT DIT DAH DIT
            elementCount = 6;
            return 0b010010;

        case '&':
            //DIT DAH DIT DIT DIT
            elementCount = 5;
            return 0b00010;

        case '\'':
            //DIT DAH DAH DAH DAH DIT
            elementCount = 6;
            return 0b011110;

        case '(':
            //DAH DIT DAH DAH DIT
            elementCount = 5;
            return 0b01101;

        case ')':
            //DAH DIT DAH DAH DIT DAH
            elementCount = 6;
            return 0b101101;

        case '+':
            //DIT DAH DIT DAH DIT
            elementCount = 5;
            return 0b01010;

        case ',':
            //DAH DAH DIT DIT DAH DAH
            elementCount = 6;
            return 0b110011;

        case '-':
            //DAH DIT DIT DIT DIT DAH
            elementCount = 6;
            return 0b100001;

        case '.':
            //DIT DAH DIT DAH DIT DAH
            elementCount = 6;
            return 0b101010;

        case '/':
            //DAH DIT DIT DAH DIT
            elementCount = 5;
            return 0b01001;

        case ':':
            //DAH DAH DAH DIT DIT DIT
            elementCount = 6;
            return 0b000111;

        case '=':
            //DAH DIT DIT DIT DAH
            elementCount = 5;
            return 0b10001;

        case '?':
            //DIT DIT DAH DAH DIT DIT
            elementCount = 6;
            return 0b001100;

        case '@':
            //DIT DAH DAH DIT DAH DIT
            elementCount = 6;
            return 0b010110;

        default:
            elementCount = 0;
            return 0;
    }
}

