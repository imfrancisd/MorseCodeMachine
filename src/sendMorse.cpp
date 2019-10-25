#include "sendMorse.h"

void sendMorse(const char message[], void (*delayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    #define DIT dotFunction(); delayFunction();
    #define DAH dashFunction(); delayFunction();

    bool hasLetterSpacing = true;

    while (true)
    {
        switch (*message)
        {
            //Digits 0-9.

            case '0':
                DAH DAH DAH DAH DAH;
                break;

            case '1':
                DIT DAH DAH DAH DAH;
                break;

            case '2':
                DIT DIT DAH DAH DAH;
                break;

            case '3':
                DIT DIT DIT DAH DAH;
                break;

            case '4':
                DIT DIT DIT DIT DAH;
                break;

            case '5':
                DIT DIT DIT DIT DIT;
                break;

            case '6':
                DAH DIT DIT DIT DIT;
                break;

            case '7':
                DAH DAH DIT DIT DIT;
                break;

            case '8':
                DAH DAH DAH DIT DIT;
                break;

            case '9':
                DAH DAH DAH DAH DIT;
                break;

            //Letters A-z and a-z.

            case 'A':
            case 'a':
                DIT DAH;
                break;

            case 'B':
            case 'b':
                DAH DIT DIT DIT;
                break;

            case 'C':
            case 'c':
                DAH DIT DAH DIT;
                break;

            case 'D':
            case 'd':
                DAH DIT DIT;
                break;

            case 'E':
            case 'e':
                DIT;
                break;

            case 'F':
            case 'f':
                DIT DIT DAH DIT;
                break;

            case 'G':
            case 'g':
                DAH DAH DIT;
                break;

            case 'H':
            case 'h':
                DIT DIT DIT DIT;
                break;

            case 'I':
            case 'i':
                DIT DIT;
                break;

            case 'J':
            case 'j':
                DIT DAH DAH DAH;
                break;

            case 'K':
            case 'k':
                DAH DIT DAH;
                break;

            case 'L':
            case 'l':
                DIT DAH DIT DIT;
                break;

            case 'M':
            case 'm':
                DAH DAH;
                break;

            case 'N':
            case 'n':
                DAH DIT;
                break;

            case 'O':
            case 'o':
                DAH DAH DAH;
                break;

            case 'P':
            case 'p':
                DIT DAH DAH DIT;
                break;

            case 'Q':
            case 'q':
                DAH DAH DIT DAH;
                break;

            case 'R':
            case 'r':
                DIT DAH DIT;
                break;

            case 'S':
            case 's':
                DIT DIT DIT;
                break;

            case 'T':
            case 't':
                DAH;
                break;

            case 'U':
            case 'u':
                DIT DIT DAH;
                break;

            case 'V':
            case 'v':
                DIT DIT DIT DAH;
                break;

            case 'W':
            case 'w':
                DIT DAH DAH;
                break;

            case 'X':
            case 'x':
                DAH DIT DIT DAH;
                break;

            case 'Y':
            case 'y':
                DAH DIT DAH DAH;
                break;

            case 'Z':
            case 'z':
                DAH DAH DIT DIT;
                break;

            //Symbols.

            case '"':
                DIT DAH DIT DIT DAH DIT;
                break;

            case '&':
                DIT DAH DIT DIT DIT;
                break;

            case '\'':
                DIT DAH DAH DAH DAH DIT;
                break;

            case '(':
                DAH DIT DAH DAH DIT;
                break;

            case ')':
                DAH DIT DAH DAH DIT DAH;
                break;

            case '+':
                DIT DAH DIT DAH DIT;
                break;

            case ',':
                DAH DAH DIT DIT DAH DAH;
                break;

            case '-':
                DAH DIT DIT DIT DIT DAH;
                break;

            case '.':
                DIT DAH DIT DAH DIT DAH;
                break;

            case '/':
                DAH DIT DIT DAH DIT;
                break;

            case ':':
                DAH DAH DAH DIT DIT DIT;
                break;

            case '=':
                DAH DIT DIT DIT DAH;
                break;

            case '?':
                DIT DIT DAH DAH DIT DIT;
                break;

            case '@':
                DIT DAH DAH DIT DAH DIT;
                break;

            //Special characters for this library.

            case '<':
                hasLetterSpacing = false;
                break;

            case '>':
                hasLetterSpacing = true;
                break;

            //Make everything else a delay between words, including the '\0'.

            default:
                //7 delays total. 3 from previous letter, 2 from here, 2 at end of loop.
                delayFunction();
                delayFunction();
                break;
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
